#!/bin/bash

# Dockerfile Validation Script
# Tests the Dockerfile structure and dependencies

echo "🔍 Dockerfile Validation for Modern Industrial HMI"
echo "=================================================="

# Check if all copied directories exist
echo "📁 Checking source directories..."

check_dir() {
    if [ -d "$1" ]; then
        echo "✅ $1 exists"
        return 0
    else
        echo "❌ $1 missing"
        return 1
    fi
}

# Essential directories
check_dir "src"
check_dir "scripts" 
check_dir "tests"
check_dir "resources"

# Check essential files
echo ""
echo "📋 Checking essential files..."
check_file() {
    if [ -f "$1" ]; then
        echo "✅ $1 exists"
        return 0
    else
        echo "❌ $1 missing"
        return 1
    fi
}

check_file "CMakeLists.txt"
check_file "README.md"

# Check Qt5 packages in current environment
echo ""
echo "🔧 Checking Qt5 development environment..."

# Check if Qt5 is available
if command -v qmake &> /dev/null; then
    echo "✅ Qt5 qmake found: $(qmake -version | grep Qt)"
else
    echo "❌ Qt5 qmake not found"
fi

# Check if CMake is available
if command -v cmake &> /dev/null; then
    echo "✅ CMake found: $(cmake --version | head -1)"
else
    echo "❌ CMake not found"
fi

# Check key Qt5 libraries
echo ""
echo "📚 Checking Qt5 libraries..."
pkg-config --exists Qt5Core && echo "✅ Qt5Core available" || echo "❌ Qt5Core missing"
pkg-config --exists Qt5Widgets && echo "✅ Qt5Widgets available" || echo "❌ Qt5Widgets missing"
pkg-config --exists Qt5Network && echo "✅ Qt5Network available" || echo "❌ Qt5Network missing"
pkg-config --exists Qt5Svg && echo "✅ Qt5Svg available" || echo "❌ Qt5Svg missing"

# Check build directories (should exist for development)
echo ""
echo "🏗️ Checking build status..."
if [ -d "build-linux-x64" ]; then
    if [ -f "build-linux-x64/bin/ModernSciFiHMI" ]; then
        echo "✅ Linux build exists and executable found"
    else
        echo "⚠️ Linux build directory exists but no executable"
    fi
else
    echo "⚠️ No Linux build directory (normal for fresh checkout)"
fi

if [ -d "build-windows-x64" ]; then
    if [ -f "build-windows-x64/bin/ModernSciFiHMI.exe" ]; then
        echo "✅ Windows build exists and executable found"
    else
        echo "⚠️ Windows build directory exists but no executable"
    fi
else
    echo "⚠️ No Windows build directory (normal for fresh checkout)"
fi

echo ""
echo "🐳 Docker context analysis..."
echo "Dockerfile size: $(wc -l < Dockerfile) lines"
echo "Source files: $(find src -name "*.cpp" -o -name "*.h" | wc -l) files"

# Check for potential Docker issues
echo ""
echo "⚠️ Potential issues to watch for:"
echo "1. MXE build takes 20-40 minutes on first run"
echo "2. Build context should exclude large directories (.dockerignore)"
echo "3. Windows cross-compilation requires significant disk space (~2GB)"

echo ""
echo "✅ Dockerfile validation complete!"
echo "Ready for: docker build -t modern-industrial-hmi ."