# Qt5 + MCP Development Container Setup

This development container provides a complete Qt5 + MCP (Model Context Protocol) development environment with AI assistance capabilities.

## 🚀 What's Included

### Development Environment
- **Ubuntu 22.04** base container
- **Qt5.15** with QML/Quick Controls
- **CMake** build system
- **GCC C++17** compiler
- **Node.js 20.x** runtime
- **Python 3.10** with pip

### MCP Servers (Pre-installed)
- **🗂️ Filesystem MCP** - File operations and project navigation
- **🧠 Memory MCP** - Persistent context across AI sessions
- **🤔 Sequential Thinking MCP** - Enhanced reasoning capabilities
- **🔧 GitHub MCP** - GitHub integration (optional)

### VS Code Extensions (Auto-installed)
- **GitHub Copilot + Chat** - AI assistance with MCP integration
- **C/C++ Tools** - IntelliSense and debugging
- **CMake Tools** - Build system integration
- **Python** - Python language support
- **Qt for Python** - Qt development support

## 🏗️ Build and Setup

### Automatic Setup
When you open this project in a dev container, everything is installed automatically:

1. **Container builds** with all dependencies
2. **MCP servers install** globally  
3. **VS Code configures** with extensions
4. **Verification script runs** to confirm setup

### Manual Build (if needed)
```bash
# Rebuild the container
docker-compose build

# Or rebuild in VS Code
Ctrl+Shift+P -> "Dev Containers: Rebuild Container"
```

## 🧪 Verification

The container automatically runs a verification script that checks:
- ✅ Node.js and Python environments
- ✅ All MCP servers installed and functional
- ✅ Qt5 modules and build tools
- ✅ VS Code configuration

You can also run verification manually:
```bash
bash .devcontainer/verify-mcp.sh
```

## 🎮 Using MCP with AI Assistance

### In VS Code with GitHub Copilot Chat:

1. **Open Copilot Chat** (Ctrl+Shift+I)
2. **Use MCP commands** with your AI assistant:

```
@filesystem show me the Qt5 project structure
@filesystem read src/main.cpp and explain the code
@filesystem create a new QML component for data visualization

@memory remember that we're building a SciFi data visualization app
@memory what were the requirements we discussed for the graph widgets?

@git show current status and recent changes
@git create a new feature branch for modbus integration
```

### Example AI-Assisted Development Flow:

```
You: "I need to create a real-time graph widget in QML for displaying sensor data"

AI: *uses filesystem MCP to scan existing code*
AI: *uses memory MCP to recall your project requirements*
AI: *creates GraphWidget.qml with perfect integration*

You: "Add this to git and explain what it does"

AI: *uses git MCP to stage and commit*
AI: *explains the component with full context*
```

## 📁 Project Structure

```
/workspaces/qpcetu/
├── .devcontainer/
│   ├── Dockerfile              # Container definition with MCP servers
│   ├── devcontainer.json       # VS Code dev container config
│   └── verify-mcp.sh          # Installation verification script
├── .vscode/
│   └── settings.json          # VS Code + MCP configuration
├── src/                       # Qt5 source code
├── CMakeLists.txt            # Build configuration
└── build/                    # Build output directory
```

## 🔧 MCP Server Details

### Filesystem MCP
- **Purpose**: File operations, code reading/writing
- **Command**: `npx @modelcontextprotocol/server-filesystem`
- **Usage**: Access project files, create components, analyze code

### Memory MCP  
- **Purpose**: Persistent context and conversation memory
- **Command**: `npx @modelcontextprotocol/server-memory`
- **Usage**: Remember project decisions, design patterns, requirements

### Sequential Thinking MCP
- **Purpose**: Enhanced reasoning and problem-solving
- **Command**: `npx @modelcontextprotocol/server-sequential-thinking`
- **Usage**: Complex development tasks, debugging, architecture

### GitHub MCP
- **Purpose**: GitHub integration and operations
- **Command**: `npx @modelcontextprotocol/server-github`
- **Usage**: Repository management, PR creation, issue tracking

## 🚀 Development Workflow

1. **Open project** in VS Code dev container
2. **Verify setup** with automatic verification
3. **Use AI assistance** with MCP-enhanced context
4. **Build Qt5 app** with CMake
5. **Git operations** through MCP integration

## 🏗️ Building the Qt5 Project

```bash
# Configure and build
mkdir -p build && cd build
cmake ..
make

# Run the application
./SciFiDataScreen
```

## 🔍 Troubleshooting

### MCP Servers Not Working
```bash
# Check installation
bash .devcontainer/verify-mcp.sh

# Reinstall if needed
npm install -g @modelcontextprotocol/server-filesystem
npm install -g @modelcontextprotocol/server-memory
npm install -g @modelcontextprotocol/server-sequential-thinking
```

### VS Code Extensions Missing
```bash
# Open Command Palette (Ctrl+Shift+P)
# Run: "Extensions: Install Extensions"
# Install: GitHub Copilot, GitHub Copilot Chat
```

### Qt5 Build Issues
```bash
# Check Qt5 installation
qmake -version
pkg-config --list-all | grep Qt5

# Verify CMake configuration
cmake --version
```

## 🎯 Ready to Develop!

Your Qt5 + MCP development environment is ready for:
- **Modern QML/Quick UI development**
- **Real-time data visualization**
- **Modbus TCP integration**  
- **AI-assisted coding with full project context**
- **Efficient git workflow with MCP integration**

Happy coding! 🎉