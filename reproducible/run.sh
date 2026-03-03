#!/bin/sh

set -e

cd "$(dirname "$0")"
./files/download.sh
sudo ./scripts/setup.sh
./scripts/build.sh
