#!/bin/sh

set -e

# Common
cd "$(dirname "$0")"
. ./common.sh
cd ../

# Copy Image
rm -f "${BUILD_IMAGE}"
cp "${IMAGE}" "${BUILD_IMAGE}"

# Start QEMU
qemu-system-arm \
    -kernel files/kernel-* \
    -cpu arm1176 \
    -m 256 \
    -M versatilepb \
    -append 'root=/dev/sda2 rootfstype=ext4 rw' \
    -hda "${BUILD_IMAGE}" \
    -nographic \
    -net nic \
    -net "user,hostfwd=tcp::${SSH_PORT}-:22" &
QEMU_PID="$!"

# Cleanup
cleanup() {
    kill "${QEMU_PID}"
    wait "${QEMU_PID}" || :
    rm -f "${BUILD_IMAGE}"
}
trap cleanup EXIT INT TERM

# Function
qemu_ssh() {
    sshpass -p "${PASSWORD}" \
        ssh \
        -p "${SSH_PORT}" \
        -o UserKnownHostsFile=/dev/null \
        -o StrictHostKeyChecking=no \
        -o ConnectTimeout=1 \
        "${USER}@localhost" \
        "$@"
}

# Wait For SSH
while ! qemu_ssh exit 2> /dev/null; do
    sleep 1
done
echo

# Build
qemu_ssh 'handheld/project/raspberry/build.sh'

# Copy
rm -rf out
mkdir -p out
download() {
    qemu_ssh "cat handheld/project/raspberry/$1" > "out/$1"
}
download 'minecraft-pi'
download 'stripped-minecraft-pi'
