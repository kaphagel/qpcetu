# SciFi Data Screen - Application Build
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

# Install all development tools
RUN apt-get update && apt-get install -y \
    build-essential cmake git wget curl unzip pkg-config \
    qtbase5-dev qttools5-dev libqt5svg5-dev libqt5network5 libqt5widgets5 \
    libmodbus-dev mingw-w64 g++-mingw-w64-x86-64 \
    autoconf automake autotools-dev libtool autopoint gettext \
    gperf bison flex intltool gdk-pixbuf2.0-dev p7zip-full lzip \
    python3-mako python3 file tree \
    && rm -rf /var/lib/apt/lists/*

RUN ln -sf /usr/bin/libtoolize /usr/bin/libtool && \
    ln -sf /usr/bin/python3 /usr/bin/python

# Build MXE Qt5 (this takes 20-40 minutes)
RUN git clone https://github.com/mxe/mxe.git /opt/mxe
WORKDIR /opt/mxe
RUN make MXE_TARGETS='x86_64-w64-mingw32.static' qtbase qtsvg qtwidgets -j$(nproc)

# Build libmodbus for Windows
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

# Application stage
FROM base as application

ENV PATH="/opt/mxe/usr/bin:$PATH"
ENV PKG_CONFIG_PATH="/opt/mxe/usr/x86_64-w64-mingw32.static/lib/pkgconfig"

WORKDIR /app

# Copy source code
COPY src/ ./src/
COPY CMakeLists.txt ./
COPY *.md ./

# Build Linux version
RUN mkdir -p build-linux && \
    cd build-linux && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make -j$(nproc)

# Build Windows version  
RUN mkdir -p build-windows && \
    cd build-windows && \
    cat > CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.16)
project(SciFiDataScreen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network Svg)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
    ../src/main.cpp
    ../src/mainwindow.cpp
    ../src/udpservice.cpp
    ../src/animatedprogressbar.cpp
    ../src/datawidget.cpp
    ../src/graphwidget.cpp
    ../src/pages/dashboardpage.cpp
    ../src/pages/graphspage.cpp
    ../src/pages/settingspage.cpp
    ../src/pages/udpresponsepage.cpp
    ../src/pages/overviewpage.cpp
    ../src/pages/dragdroppage_simple.cpp
)

set(HEADERS
    ../src/mainwindow.h
    ../src/udpservice.h
    ../src/animatedprogressbar.h
    ../src/datawidget.h
    ../src/graphwidget.h
    ../src/pages/dashboardpage.h
    ../src/pages/graphspage.h
    ../src/pages/settingspage.h
    ../src/pages/udpresponsepage.h
    ../src/pages/overviewpage.h
    ../src/pages/dragdroppage_simple.h
)

# Add Qt resources for icons
qt5_add_resources(ICON_RESOURCES ../resources/icons/overview.qrc)

add_executable(SciFiDataScreen ${SOURCES} ${HEADERS} ${ICON_RESOURCES})

target_link_libraries(SciFiDataScreen 
    Qt5::Core Qt5::Widgets Qt5::Network Qt5::Svg
)

target_include_directories(SciFiDataScreen PRIVATE 
    ../src
    /opt/libmodbus-windows/include
)

if(WIN32 OR MINGW)
    target_link_libraries(SciFiDataScreen 
        ws2_32 iphlpapi
        /opt/libmodbus-windows/lib/libmodbus.a
    )
    set_target_properties(SciFiDataScreen PROPERTIES
        LINK_FLAGS "-static -static-libgcc -static-libstdc++"
        WIN32_EXECUTABLE TRUE
    )
endif()
EOF

RUN cd build-windows && \
    cmake -DCMAKE_TOOLCHAIN_FILE=/opt/mxe/usr/x86_64-w64-mingw32.static/share/cmake/mxe-conf.cmake \
          -DCMAKE_BUILD_TYPE=Release . && \
    make -j$(nproc)

# Create Windows batch launcher
RUN cd build-windows && \
    cat > start_scifi_datascreen.bat << 'EOF'
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
EOF

# Create deployment info
RUN echo "=== SciFi Data Screen Build Summary ===" > /app/BUILD_INFO.txt && \
    echo "Build Date: $(date)" >> /app/BUILD_INFO.txt && \
    echo "Linux Executable:" >> /app/BUILD_INFO.txt && \
    ls -lh build-linux/SciFiDataScreen >> /app/BUILD_INFO.txt 2>/dev/null || echo "  Build failed" >> /app/BUILD_INFO.txt && \
    echo "Windows Executable:" >> /app/BUILD_INFO.txt && \
    ls -lh build-windows/SciFiDataScreen.exe >> /app/BUILD_INFO.txt 2>/dev/null || echo "  Build failed" >> /app/BUILD_INFO.txt && \
    echo "" >> /app/BUILD_INFO.txt && \
    echo "Deployment files in /app/build-windows/ and /app/build-linux/" >> /app/BUILD_INFO.txt

EXPOSE 3250/udp

CMD cat /app/BUILD_INFO.txt && /bin/bash