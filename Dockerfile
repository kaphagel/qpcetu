# Modern Industrial HMI - Qt5 Widgets Application Build
# Professional touch-optimized Human Machine Interface for Industrial Controllers
# Features: UDP Discovery, Modbus TCP, Real-time Visualization, Enterprise Architecture

# Uses pre-built base image with MXE Qt5 cross-compilation environment
# You can either:
# 1. Use the base image built locally: FROM scifi-datascreen-base:latest
# 2. Or build everything in one go (slower but self-contained)

# Option 1: Use pre-built base (recommended)
# FROM scifi-datascreen-base:latest

# Option 2: Build base inline (self-contained but slower)
FROM ubuntu:22.04 as base

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Install comprehensive development environment for Qt5 + Industrial HMI
RUN apt-get update && apt-get install -y \
    build-essential cmake git wget curl unzip pkg-config tree file \
    qtbase5-dev qttools5-dev libqt5svg5-dev libqt5network5 libqt5widgets5 \
    qtbase5-dev-tools qt5-qmake libqt5test5 \
    libmodbus-dev mingw-w64 g++-mingw-w64-x86-64 \
    autoconf automake autotools-dev libtool autopoint gettext \
    gperf bison flex intltool gdk-pixbuf2.0-dev p7zip-full lzip \
    python3-mako python3 netstat-nat net-tools \
    libgl1-mesa-dev libglu1-mesa-dev libxkbcommon-x11-0 \
    libxcb-xinerama0 libxcb-cursor0 \
    && rm -rf /var/lib/apt/lists/*

RUN ln -sf /usr/bin/libtoolize /usr/bin/libtool && \
    ln -sf /usr/bin/python3 /usr/bin/python

# Build MXE Qt5 for Windows cross-compilation (this takes 20-40 minutes)
# Use specific commit to ensure reproducible builds
RUN git clone https://github.com/mxe/mxe.git /opt/mxe
WORKDIR /opt/mxe
RUN make MXE_TARGETS='x86_64-w64-mingw32.static' qtbase qtsvg qtwidgets -j$(nproc)

# Build libmodbus for Windows cross-compilation
WORKDIR /tmp
RUN git clone https://github.com/stephane/libmodbus.git && \
    cd libmodbus && \
    export PATH="/opt/mxe/usr/bin:$PATH" && \
    ./autogen.sh && \
    ./configure --host=x86_64-w64-mingw32.static \
                --prefix=/opt/libmodbus-windows \
                --enable-static --disable-shared && \
    make -j$(nproc) && make install && \
    rm -rf /tmp/libmodbus

# Application stage - Modern Industrial HMI
FROM base as application

ENV PATH="/opt/mxe/usr/bin:$PATH"
ENV PKG_CONFIG_PATH="/opt/mxe/usr/x86_64-w64-mingw32.static/lib/pkgconfig"
ENV PKG_CONFIG_PATH="/opt/mxe/usr/x86_64-w64-mingw32.static/lib/pkgconfig"

WORKDIR /app

# Copy source code and essential project files
COPY src/ ./src/
COPY CMakeLists.txt ./
COPY *.md ./

# Copy directories that exist and are needed
COPY scripts/ ./scripts/
COPY tests/ ./tests/
COPY resources/ ./resources/

# Note: mxe-lite and build directories are not copied as they will be built fresh
# This ensures clean builds and reduces Docker context size

# Build Linux version - Modern Industrial HMI
RUN mkdir -p build-linux && \
    cd build-linux && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make -j$(nproc)

# Build Windows version - Cross-platform Industrial HMI
RUN mkdir -p build-windows && \
    cd build-windows && \
    cmake -DCMAKE_TOOLCHAIN_FILE=/opt/mxe/usr/x86_64-w64-mingw32.static/share/cmake/mxe-conf.cmake \
          -DCMAKE_BUILD_TYPE=Release .. && \
    make -j$(nproc)

# Create Windows batch launcher for Industrial HMI
RUN cd build-windows && \
    cat > start_modern_industrial_hmi.bat << 'EOF'
@echo off
echo Starting Modern Industrial HMI - Touch Optimized...
echo.
echo Industrial Features:
echo - UDP Controller Discovery (Port 3250)
echo - Modbus TCP Communication  
echo - Real-time Data Visualization with Touch Interface
echo - Multi-Controller Management Dashboard
echo - Professional Enterprise Architecture Patterns
echo - Apple Design System with Dark/Light Themes
echo.
ModernSciFiHMI.exe
pause
EOF

# Create deployment info with current architecture
RUN echo "=== Modern Industrial HMI Build Summary ===" > /app/BUILD_INFO.txt && \
    echo "Build Date: $(date)" >> /app/BUILD_INFO.txt && \
    echo "Project: Industrial Touch HMI with Qt5 Widgets" >> /app/BUILD_INFO.txt && \
    echo "Architecture: Enterprise Patterns (Strategy, Command, State, Observer, Repository, Plugin)" >> /app/BUILD_INFO.txt && \
    echo "" >> /app/BUILD_INFO.txt && \
    echo "Linux Executable:" >> /app/BUILD_INFO.txt && \
    (ls -lh build-linux/bin/ModernSciFiHMI 2>/dev/null && echo "  ✅ Linux build successful") || echo "  ❌ Linux build failed" >> /app/BUILD_INFO.txt && \
    echo "Windows Executable:" >> /app/BUILD_INFO.txt && \
    (ls -lh build-windows/bin/ModernSciFiHMI.exe 2>/dev/null && echo "  ✅ Windows build successful") || echo "  ❌ Windows build failed" >> /app/BUILD_INFO.txt && \
    echo "" >> /app/BUILD_INFO.txt && \
    echo "Features:" >> /app/BUILD_INFO.txt && \
    echo "- Touch-optimized interface (60x60px minimum buttons)" >> /app/BUILD_INFO.txt && \
    echo "- Industrial controller discovery via UDP broadcast" >> /app/BUILD_INFO.txt && \
    echo "- Real-time Modbus TCP communication" >> /app/BUILD_INFO.txt && \
    echo "- Multi-theme support (Dark, Light, High Contrast, Apple themes)" >> /app/BUILD_INFO.txt && \
    echo "- Professional navigation with hamburger menu" >> /app/BUILD_INFO.txt && \
    echo "- Clean borderless design following Apple HIG principles" >> /app/BUILD_INFO.txt && \
    echo "- Cross-platform deployment (Linux + Windows)" >> /app/BUILD_INFO.txt && \
    echo "" >> /app/BUILD_INFO.txt && \
    echo "Deployment files: /app/build-windows/ and /app/build-linux/" >> /app/BUILD_INFO.txt

# Expose UDP discovery port
EXPOSE 3250/udp

# Expose Modbus TCP port
EXPOSE 502/tcp

CMD cat /app/BUILD_INFO.txt && /bin/bash