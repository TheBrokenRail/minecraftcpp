#!/bin/sh

set -e

# Require Root
if [ ! "$(id -u)" -eq 0 ]; then
    echo 'Run As Root!' > /dev/stderr
    exit 1
fi

# Common
cd "$(dirname "$0")"
. ./common.sh
cd ../

# Make Image
rm -f "${OS_VERSION}.img"
unzip "files/${OS_VERSION}.zip"
rm -f "${IMAGE}"
qemu-img convert -f raw -O qcow2 "${OS_VERSION}.img" "${IMAGE}"
rm "${OS_VERSION}.img"

# Expand Image
qemu-img resize "${IMAGE}" +8G

# Attach Image
modprobe nbd max_part=8
DEVICE="/dev/nbd0"
qemu-nbd --disconnect "${DEVICE}"
qemu-nbd "--connect=${DEVICE}" "${IMAGE}"
sleep 0.5

# Expand File-System
PARTITION="2"
parted "${DEVICE}" resizepart "${PARTITION}" 100%
partprobe "${DEVICE}"
resize2fs -f "${DEVICE}p${PARTITION}"

# Mount
rm -rf mnt
mkdir -p mnt
mount "${DEVICE}p${PARTITION}" mnt

# Setup
truncate -s0 mnt/etc/ld.so.preload
sed -i 's/mmcblk0p/sda/g' mnt/etc/fstab
dpkg --force-all --unpack "--root=$(pwd)/mnt" "--admindir=$(pwd)/mnt/var/lib/dpkg" files/*.deb
cp -ar ../handheld mnt/home/pi

# Unmount
sync mnt
while ! umount mnt 2> /dev/null; do
    sleep 1
done
rm -rf mnt

# Detach Image
qemu-nbd --disconnect "${DEVICE}"
sleep 0.5
rmmod nbd
