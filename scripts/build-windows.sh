#!/bin/bash

echo "Building Touch-Optimized SciFi HMI for Windows (Cross-compilation via MXE)"

# Create and navigate to Windows build directory
mkdir -p ../build-windows-x64
cd ../build-windows-x64

# Set MXE environment (updated for deps structure)
export PATH="/workspaces/qpcetu/deps/toolchain/mxe-lite/usr/bin:$PATH"

# Clean previous build
rm -rf CMakeCache.txt CMakeFiles/

# Configure using MXE wrapper script (recommended approach)
/workspaces/qpcetu/deps/toolchain/mxe-lite/usr/bin/x86_64-w64-mingw32.static-cmake \
    -DCMAKE_BUILD_TYPE=Release ..

# Build only the touch-optimized version
make -j$(nproc)

echo "Windows touch-optimized build complete!"
echo "Executable created:"
echo "- bin/ModernSciFiHMI.exe (Touch-Optimized Industrial HMI)"