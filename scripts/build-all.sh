#!/bin/bash

# Quantum Tactical Processing Center - Universal Build Script
# This script builds both Linux and Windows versions

echo "🚀 Building All Platforms - Quantum Tactical Processing Center - ETU"
echo "================================================================"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "🐧 Building Linux version..."
echo "----------------------------"
cd "$SCRIPT_DIR"
if ./build-linux.sh; then
    echo "✅ Linux build successful!"
else
    echo "❌ Linux build failed!"
    exit 1
fi

echo ""
echo "🪟 Building Windows version..."
echo "------------------------------"
cd "$SCRIPT_DIR"
if ./build-windows.sh; then
    echo "✅ Windows build successful!"
else
    echo "❌ Windows build failed!"
    exit 1
fi

echo ""
echo "🎉 All builds completed successfully!"
echo "======================================"
echo ""
echo "📦 Build Output:"
echo "  Linux:   build-linux-x64/bin/ModernSciFiHMI"
echo "  Windows: build-windows-x64/bin/ModernSciFiHMI.exe"
echo ""
echo "🌟 Ready for deployment!"