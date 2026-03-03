#!/bin/sh

set -e

# Common
cd "$(dirname "$0")"
. ../scripts/common.sh

# Download
download() {
    wget --no-clobber --no-check-certificate "$1"
}
download 'https://github.com/dhruvvyas90/qemu-rpi-kernel/raw/refs/heads/master/kernel-qemu-4.4.34-jessie'
download "https://downloads.raspberrypi.org/raspbian/images/${OS_VERSION}/${OS_VERSION}.zip"
download 'https://legacy.raspbian.org/raspbian/pool/main/libs/libsdl1.2/libsdl1.2-dev_1.2.15-5_armhf.deb'
download 'https://legacy.raspbian.org/raspbian/pool/main/libx/libx11/libx11-dev_1.5.0-1%2Bdeb7u4_armhf.deb'
download 'https://legacy.raspbian.org/raspbian/pool/main/libp/libpng/libpng12-0_1.2.49-1%2Bdeb7u2_armhf.deb'
download 'https://legacy.raspbian.org/raspbian/pool/main/libp/libpng/libpng12-dev_1.2.49-1%2Bdeb7u2_armhf.deb'
download 'https://legacy.raspbian.org/raspbian/pool/main/x/x11proto-core/x11proto-core-dev_7.0.23-1_all.deb'
