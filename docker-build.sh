#!/bin/bash

# Docker build script for SciFi Data Screen
# This script provides different build strategies for different use cases

set -e

echo "🚀 SciFi Data Screen - Docker Build Script"
echo "=========================================="

# Check if Docker is available
if ! command -v docker &> /dev/null; then
    echo "❌ Docker is not installed or not in PATH"
    exit 1
fi

# Build options
case "${1:-full}" in
    "base")
        echo "🔨 Building base image with MXE Qt5 cross-compilation environment..."
        echo "⚠️  This will take 20-40 minutes but only needs to be done once"
        echo ""
        
        docker build -f Dockerfile.base -t scifi-datascreen-base:latest .
        
        echo ""
        echo "✅ Base image built successfully!"
        echo "💡 You can now use 'build-app' for faster application builds"
        ;;
        
    "app")
        echo "🔨 Building application using pre-built base image..."
        
        # Check if base image exists
        if ! docker image inspect scifi-datascreen-base:latest > /dev/null 2>&1; then
            echo "❌ Base image not found. Please run './docker-build.sh base' first"
            exit 1
        fi
        
        # Create temporary Dockerfile using base image
        cat > Dockerfile.app << 'EOF'
FROM scifi-datascreen-base:latest

WORKDIR /app
COPY src/ ./src/
COPY CMakeLists.txt ./
COPY *.md ./

# Build Linux version
RUN mkdir -p build-linux && \
    cd build-linux && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make -j$(nproc)

# Build Windows version
COPY build-windows/CMakeLists.txt ./build-windows/
RUN cd build-windows && \
    cmake -DCMAKE_TOOLCHAIN_FILE=/opt/mxe/usr/x86_64-w64-mingw32.static/share/cmake/mxe-conf.cmake \
          -DCMAKE_BUILD_TYPE=Release . && \
    make -j$(nproc) && \
    cat > start_scifi_datascreen.bat << 'BATCH'
@echo off
echo Starting SciFi Data Screen for Windows...
echo.
echo Features:
echo - UDP Industrial Module Discovery (Port 3250)
echo - Modbus TCP Communication
echo - Real-time Data Visualization
echo - Multi-page Dashboard Interface
echo.
SciFiDataScreen.exe
pause
BATCH

RUN echo "=== Build Summary ===" > /app/BUILD_INFO.txt && \
    echo "Linux: $(ls -lh build-linux/SciFiDataScreen 2>/dev/null || echo 'Failed')" >> /app/BUILD_INFO.txt && \
    echo "Windows: $(ls -lh build-windows/SciFiDataScreen.exe 2>/dev/null || echo 'Failed')" >> /app/BUILD_INFO.txt

CMD cat /app/BUILD_INFO.txt && /bin/bash
EOF

        docker build -f Dockerfile.app -t scifi-datascreen:latest .
        rm -f Dockerfile.app
        
        echo ""
        echo "✅ Application built successfully!"
        ;;
        
    "full")
        echo "🔨 Building complete application (self-contained)..."
        echo "⚠️  This will take 20-40 minutes as it builds MXE from scratch"
        echo ""
        
        docker build -f Dockerfile -t scifi-datascreen:latest .
        
        echo ""
        echo "✅ Full application built successfully!"
        ;;
        
    "extract")
        echo "📦 Extracting built executables from Docker image..."
        
        # Check if image exists
        if ! docker image inspect scifi-datascreen:latest > /dev/null 2>&1; then
            echo "❌ Application image not found. Please build it first."
            exit 1
        fi
        
        # Create output directory
        mkdir -p docker-output
        
        # Extract files
        docker run --rm -v "$(pwd)/docker-output:/output" scifi-datascreen:latest sh -c "
            cp build-linux/SciFiDataScreen /output/ 2>/dev/null || echo 'Linux build not found'
            cp build-windows/SciFiDataScreen.exe /output/ 2>/dev/null || echo 'Windows .exe not found'
            cp build-windows/start_scifi_datascreen.bat /output/ 2>/dev/null || echo 'Batch file not found'
            echo 'Files extracted to docker-output/'
        "
        
        echo ""
        echo "✅ Files extracted to docker-output/"
        ls -lh docker-output/
        ;;
        
    "run")
        echo "🏃 Running SciFi Data Screen container..."
        
        docker run --rm -it \
            --name scifi-datascreen \
            -p 3250:3250/udp \
            scifi-datascreen:latest
        ;;
        
    "clean")
        echo "🧹 Cleaning up Docker images..."
        
        docker rmi scifi-datascreen:latest 2>/dev/null || true
        docker rmi scifi-datascreen-base:latest 2>/dev/null || true
        rm -rf docker-output
        
        echo "✅ Cleanup complete"
        ;;
        
    *)
        echo "Usage: $0 [command]"
        echo ""
        echo "Commands:"
        echo "  base     - Build base image with MXE Qt5 (slow, one-time)"
        echo "  app      - Build application using base image (fast)"
        echo "  full     - Build complete application (self-contained, slow)"
        echo "  extract  - Extract executables from built image"
        echo "  run      - Run the application container"
        echo "  clean    - Remove Docker images and output files"
        echo ""
        echo "Recommended workflow:"
        echo "  1. $0 base      # Build base (once)"
        echo "  2. $0 app       # Build app (repeat as needed)"
        echo "  3. $0 extract   # Get executables"
        echo ""
        echo "Or for one-time builds:"
        echo "  1. $0 full      # Build everything"
        echo "  2. $0 extract   # Get executables"
        ;;
esac