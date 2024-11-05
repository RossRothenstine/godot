#!/usr/bin/env bash

## Download Swappy from the latest github release and extracts it to
# thirdparty/swappy-frame-pacing

set -e
SWAPPY_VERSION="v2023.3.0.0"
SWAPPY_URL="https://github.com/darksylinc/godot-swappy/releases/download/${SWAPPY_VERSION}/godot-swappy.7z"

# Download Swappy
wget -O swappy.7z "${SWAPPY_URL}"
if [ ! -f swappy.7z ]; then
    echo "Failed to download Swappy"
    exit 1
fi

# Extract Swappy
7z x swappy.7z -othirdparty/swappy-frame-pacing -y

# Cleanup
rm swappy.7z
