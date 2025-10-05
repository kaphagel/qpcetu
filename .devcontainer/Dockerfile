# Use official Ubuntu 22.04 base
FROM mcr.microsoft.com/vscode/devcontainers/base:jammy

# Avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update and enable universe repo
RUN apt-get update && apt-get install -y software-properties-common \
    && add-apt-repository universe \
    && apt-get update

# Install Node.js 20.x repository
RUN curl -fsSL https://deb.nodesource.com/setup_20.x | bash -

# Install development tools, Qt5, QML modules, Node.js, and Python
RUN apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    gdb \
    git \
    pkg-config \
    curl \
    wget \
    nodejs \
    python3 \
    python3-pip \
    python3-venv \
    qt5-qmake \
    qtbase5-dev \
    qtbase5-dev-tools \
    qtdeclarative5-dev \
    libqt5svg5-dev \
    qml-module-qtquick2 \
    qml-module-qtquick-controls \
    qml-module-qtquick-controls2 \
    qml-module-qtquick-window2 \
    qml-module-qtquick-dialogs \
    qml-module-qtquick-xmllistmodel \
    libmodbus-dev \
    libbsd-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    x11-apps \
    sudo \
    && rm -rf /var/lib/apt/lists/*

# Install Node.js MCP servers globally (with proper permissions)
RUN npm install -g \
    @modelcontextprotocol/server-filesystem \
    @modelcontextprotocol/server-memory \
    @modelcontextprotocol/server-sequential-thinking \
    @modelcontextprotocol/server-github

# Install Python MCP packages
RUN pip3 install --upgrade pip \
    && pip3 install mcp

# Create MCP configuration directory
RUN mkdir -p /home/vscode/.config/mcp

# Set Qt platform for X11
ENV QT_QPA_PLATFORM=xcb

# Verify installations
RUN echo "🔍 Verifying installations..." \
    && node --version \
    && npm --version \
    && python3 --version \
    && qmake -version \
    && dpkg -l | grep -q libqt5svg5-dev && echo "✅ Qt5 SVG support installed" \
    && dpkg -l | grep -q libbsd-dev && echo "✅ BSD library support installed" \
    && echo "✅ Qt5 + MCP development environment installed!"

# Create workspace directory
RUN mkdir -p /workspace
WORKDIR /workspace

# Set proper ownership for vscode user
RUN chown -R vscode:vscode /home/vscode/.config

# Switch to non-root user
USER vscode

# Print info
CMD ["bash", "-c", "echo '🎉 Qt5 + MCP development environment ready!' && bash"]
