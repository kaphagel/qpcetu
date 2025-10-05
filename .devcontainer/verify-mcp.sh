#!/bin/bash
# MCP Server Installation Verification Script

echo "🔍 Verifying MCP Server Installation..."
echo "======================================="

# Check runtime environments
echo ""
echo "🛠️  Runtime Environments:"
echo "Node.js: $(node --version)"
echo "NPM: $(npm --version)"
echo "Python: $(python3 --version)"

# Verify MCP servers are installed
echo ""
echo "📦 Checking MCP Server Installations:"

# Node.js MCP servers
echo ""
echo "Node.js MCP Servers:"
if npm list -g @modelcontextprotocol/server-filesystem >/dev/null 2>&1; then
    echo "✅ Filesystem MCP Server: Installed"
else
    echo "❌ Filesystem MCP Server: Missing"
fi

if npm list -g @modelcontextprotocol/server-memory >/dev/null 2>&1; then
    echo "✅ Memory MCP Server: Installed"
else
    echo "❌ Memory MCP Server: Missing"
fi

if npm list -g @modelcontextprotocol/server-sequential-thinking >/dev/null 2>&1; then
    echo "✅ Sequential Thinking MCP Server: Installed"
else
    echo "❌ Sequential Thinking MCP Server: Missing"
fi

if npm list -g @modelcontextprotocol/server-github >/dev/null 2>&1; then
    echo "✅ GitHub MCP Server: Installed"
else
    echo "❌ GitHub MCP Server: Missing"
fi

# Python MCP packages
echo ""
echo "Python MCP Packages:"
if python3 -c "import mcp" 2>/dev/null; then
    echo "✅ MCP Python SDK: Installed"
else
    echo "❌ MCP Python SDK: Missing"
fi

# Check Qt5 installation
echo ""
echo "🔧 Qt5 Environment:"
echo "QMake: $(qmake -version 2>&1 | head -1)"

# Check Qt5 modules
echo "Qt5 Modules:"
for module in Qt5Core Qt5Widgets Qt5Network Qt5Quick Qt5Qml; do
    if pkg-config --exists $module 2>/dev/null; then
        version=$(pkg-config --modversion $module)
        echo "✅ $module: $version"
    else
        echo "❌ $module: Missing"
    fi
done

# Check MCP configuration directory
echo ""
echo "📁 MCP Configuration:"
if [ -d "/home/vscode/.config/mcp" ]; then
    echo "✅ MCP config directory: /home/vscode/.config/mcp"
else
    echo "❌ MCP config directory: Missing"
fi

# Test basic functionality
echo ""
echo "🧪 Basic Functionality Tests:"

# Test Node.js MCP servers
if npx @modelcontextprotocol/server-filesystem --help >/dev/null 2>&1; then
    echo "✅ Filesystem MCP: Functional"
else
    echo "❌ Filesystem MCP: Not functional"
fi

if npx @modelcontextprotocol/server-memory --help >/dev/null 2>&1; then
    echo "✅ Memory MCP: Functional"
else
    echo "❌ Memory MCP: Not functional"
fi

# Check CMake and build tools
echo ""
echo "🏗️  Build Environment:"
echo "CMake: $(cmake --version | head -1)"
echo "GCC: $(gcc --version | head -1)"
echo "Make: $(make --version | head -1)"

echo ""
echo "🎉 MCP + Qt5 development environment verification complete!"
echo ""
echo "📋 Next Steps:"
echo "1. Open VS Code in this dev container"
echo "2. Install GitHub Copilot Chat extension"
echo "3. Configure MCP servers in VS Code settings"
echo "4. Start Qt5 development with AI assistance!"