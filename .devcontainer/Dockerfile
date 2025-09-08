FROM mcr.microsoft.com/devcontainers/base:noble

# Avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update package list and install Qt5 and development tools
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    qtbase5-dev \
    qtbase5-dev-tools \
    libqt5core5a \
    libqt5widgets5 \
    libqt5gui5 \
    qt5-qmake \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libxkbcommon-x11-0 \
    libxcb-xinerama0 \
    libxcb-cursor0 \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Set environment variables for Qt
ENV QT_QPA_PLATFORM=xcb

# Create workspace directory
RUN mkdir -p /workspace
WORKDIR /workspace

# Switch back to vscode user
USER vscode