#!/bin/bash

# Quantum Tactical Processing Center - Build Script
# This script builds the Qt sci-fi application

echo "🚀 Building Quantum Tactical Processing Center - ETU..."
echo "=================================================="

# Check if Qt5 is available
if ! command -v qmake &> /dev/null; then
    echo "❌ Qt5 not found. Please install Qt5 development packages:"
    echo "   Ubuntu/Debian: sudo apt install qtbase5-dev"
    echo "   Fedora: sudo dnf install qt5-qtbase-devel"
    echo "   Arch: sudo pacman -S qt5-base"
    exit 1
fi

# Check if CMake is available
if ! command -v cmake &> /dev/null; then
    echo "❌ CMake not found. Please install CMake:"
    echo "   Ubuntu/Debian: sudo apt install cmake"
    echo "   Fedora: sudo dnf install cmake"
    echo "   Arch: sudo pacman -S cmake"
    exit 1
fi

# Create build directory (relative to project root)
if [ ! -d "../build-linux-x64" ]; then
    echo "📁 Creating build directory..."
    mkdir ../build-linux-x64
fi

cd ../build-linux-x64

# Configure with CMake
echo "⚙️  Configuring with CMake..."
if ! cmake ..; then
    echo "❌ CMake configuration failed!"
    exit 1
fi

# Build the application
echo "🔨 Building application..."
if ! make -j$(nproc); then
    echo "❌ Build failed!"
    exit 1
fi

echo ""
echo "✅ Build completed successfully!"
echo ""
echo "🎯 To run the application:"
echo "   cd build-linux-x64"
echo "   ./bin/ModernSciFiHMI"
echo ""
echo "🌟 Enjoy your futuristic sci-fi data screen!"
