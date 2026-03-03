#!/bin/sh

set -e

# Set Directory
cd "$(dirname "$0")"
ROOT="$(pwd)"

# Build RakNet
cd ../lib_projects/raknet/jni/RaknetSources
make clean
make -j$(nproc)

# Build
cd "${ROOT}"
make clean
make -j$(nproc)

# Strip
cp minecraft-pi stripped-minecraft-pi
strip stripped-minecraft-pi
