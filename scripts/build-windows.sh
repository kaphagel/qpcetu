#!/bin/bash

echo "Building Touch-Optimized SciFi HMI for Windows (Cross-compilation via MXE)"

# Get the project root directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build-windows-x64"
MXE_PATH="$PROJECT_ROOT/deps/toolchain/mxe-lite/usr/bin"

# Create and navigate to Windows build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Set MXE environment (updated for deps structure)
export PATH="$MXE_PATH:$PATH"

# Clean previous build
rm -rf CMakeCache.txt CMakeFiles/

# Configure using MXE wrapper script (recommended approach)
"$MXE_PATH/x86_64-w64-mingw32.static-cmake" \
    -DCMAKE_BUILD_TYPE=Release "$PROJECT_ROOT"

# Build only the touch-optimized version
make -j$(nproc)

echo "Windows touch-optimized build complete!"
echo "Executable created:"
echo "- bin/ModernSciFiHMI.exe (Touch-Optimized Industrial HMI)"