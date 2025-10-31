# Dependencies Management

## Industrial HMI External Dependencies

This directory contains external libraries, toolchains, and dependencies for the Qt5-based industrial HMI system.

## 📂 Directory Structure

### **[external/](./external/)**
External libraries and third-party components.
- **libmodbus**: Industrial Modbus TCP communication library
- Future external libraries as needed

### **[toolchain/](./toolchain/)**
Cross-compilation toolchains and build tools.
- **MXE (M Cross Environment)**: Windows cross-compilation environment
- Platform-specific build tools and environments

### **[windows/](./windows/)**
Windows-specific dependencies and libraries.
- **libmodbus-windows**: Windows-compiled libmodbus libraries
- Windows-specific build artifacts and installations

## 🔧 Dependency Management Strategy

### **Version Control Integration**
- **Git Submodules**: External libraries tracked as submodules for version consistency
- **Gitignore**: Large toolchain downloads excluded from repository
- **Version Pinning**: Specific versions documented for reproducible builds

### **Build System Integration**
All dependencies integrate with the professional build system:
```bash
# Dependencies are automatically resolved by build scripts
./scripts/build-linux.sh    # Uses system Qt5 + external/libmodbus
./scripts/build-windows.sh  # Uses MXE toolchain + windows/libmodbus
./scripts/build-all.sh      # Handles both platforms appropriately
```

### **Cross-Platform Compatibility**
- **Linux**: Uses system package manager + external source builds
- **Windows**: Uses MXE cross-compilation + pre-built libraries
- **Future Platforms**: ARM, macOS support structure ready

## 📦 Current Dependencies

### **libmodbus** - Industrial Communication
- **Version**: Latest stable from upstream
- **Purpose**: Modbus TCP client/server communication
- **Platforms**: Linux (source), Windows (pre-built)
- **Location**: 
  - `deps/external/libmodbus/` - Source code
  - `deps/windows/libmodbus-windows/` - Windows binaries

### **Qt5** - GUI Framework
- **Version**: 5.15+ (system-provided)
- **Purpose**: Widgets-based touch-optimized GUI
- **Platforms**: Linux (package manager), Windows (MXE)
- **Modules**: Core, Widgets, Network, Svg

### **MXE Cross-Compilation Toolchain**
- **Version**: Latest stable
- **Purpose**: Windows cross-compilation from Linux
- **Platform**: Linux host → Windows target
- **Location**: `deps/toolchain/mxe-lite/` (when present)

## 🚀 Dependency Installation

### **Linux Development Environment**
```bash
# System dependencies via package manager
sudo apt install qtbase5-dev qtdeclarative5-dev libqt5svg5-dev cmake build-essential

# External dependencies built automatically by build scripts
./scripts/build-linux.sh
```

### **Windows Cross-Compilation Setup**
```bash
# MXE toolchain setup (one-time, 20-40 minutes)
cd deps/toolchain/mxe-lite
make MXE_TARGETS='x86_64-w64-mingw32.static' qtbase qtsvg qtwidgets

# Windows build with all dependencies
./scripts/build-windows.sh
```

### **Automated Dependency Resolution**
The professional build system automatically handles dependencies:
- **Detection**: Checks for required dependencies before building
- **Setup**: Downloads and configures missing dependencies
- **Caching**: Reuses built dependencies for faster subsequent builds
- **Validation**: Verifies dependency versions and compatibility

## 🔄 Dependency Updates

### **Updating External Libraries**
```bash
# Update libmodbus to latest version
cd deps/external/libmodbus
git pull origin master

# Rebuild with updated dependency
./scripts/build-all.sh
```

### **Toolchain Updates**
```bash
# Update MXE toolchain
cd deps/toolchain/mxe-lite
git pull origin master
make clean
make MXE_TARGETS='x86_64-w64-mingw32.static' qtbase qtsvg qtwidgets
```

### **Windows Dependencies**
```bash
# Update Windows-specific libraries
# Manual process - download new versions to deps/windows/
# Update CMakeLists.txt paths accordingly
```

## 🧪 Dependency Testing

### **Validation Commands**
```bash
# Verify all dependencies present and working
./scripts/build-all.sh

# Check dependency versions
./scripts/check-dependencies.sh  # (future script)

# Test cross-platform compatibility
./scripts/test-cross-platform.sh  # (future script)
```

### **Dependency Isolation**
- **Containerized Builds**: Docker support for isolated dependency management
- **Virtual Environments**: Separate build environments for different configurations
- **Clean Builds**: Scripts to rebuild from scratch with fresh dependencies

## 📋 Adding New Dependencies

### **External Library Integration**
1. **Add as Submodule**: `git submodule add <url> deps/external/<name>`
2. **Update CMakeLists.txt**: Add dependency detection and linking
3. **Update Build Scripts**: Ensure dependency built for all platforms
4. **Document Integration**: Update this README and build documentation

### **Platform-Specific Dependencies**
1. **Linux**: Add to apt/dnf package lists in build scripts
2. **Windows**: Add pre-built libraries to `deps/windows/`
3. **Cross-Platform**: Use CMake find_package() for detection
4. **Documentation**: Update deployment documentation

## 🔒 Security Considerations

### **Dependency Scanning**
- **Known Vulnerabilities**: Regular security scanning of external dependencies
- **Version Pinning**: Specific versions to avoid supply chain attacks
- **Verification**: Checksum verification for downloaded dependencies
- **Isolation**: Sandboxed build environments for untrusted dependencies

### **Supply Chain Security**
- **Trusted Sources**: Dependencies only from trusted, official repositories
- **Submodule Integrity**: Git submodules for version control integration
- **Build Reproducibility**: Deterministic builds with fixed dependency versions
- **Security Updates**: Process for rapid security update deployment

## 📞 Dependency Support

For dependency-related issues:
1. Check the [Build System Documentation](../docs/development/build-system.md)
2. Review the [Deployment Documentation](../docs/deployment/README.md)
3. Verify dependency versions and compatibility
4. Test with clean build environment

## 🎯 Future Dependency Management

### **Planned Improvements**
- **Package Manager**: Conan or vcpkg integration for C++ dependencies
- **Automated Updates**: CI/CD pipeline for dependency updates and testing
- **Multi-Platform**: Extended support for ARM, macOS platforms
- **Container Registry**: Docker-based dependency distribution

### **Dependency Roadmap**
- **libmodbus**: Continue tracking upstream, consider alternatives
- **Qt Framework**: Plan Qt6 migration for future versions
- **Build Tools**: CMake upgrades, modern C++ toolchain support
- **Testing**: Automated dependency compatibility testing

---

**Last Updated**: October 30, 2025
**Status**: Professional structure implementation in progress (Step 4)