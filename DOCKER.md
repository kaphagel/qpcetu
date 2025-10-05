# Docker Deployment Guide for SciFi Data Screen

This guide explains how to build and deploy the SciFi Data Screen application using Docker, including cross-compilation for Windows.

## 🎯 Overview

The Docker setup provides:
- **Linux executable** - Native Qt5 GUI application
- **Windows executable** - Cross-compiled Qt5 GUI application (.exe)
- **Industrial protocols** - UDP discovery + Modbus TCP support
- **Standalone deployment** - No external dependencies needed

## 🚀 Quick Start

### Option 1: Simple Build (Everything in one go)

```bash
# Build complete application (takes 20-40 minutes)
./docker-build.sh full

# Extract executables
./docker-build.sh extract

# Your files are now in docker-output/
ls -la docker-output/
```

### Option 2: Optimized Build (Faster for development)

```bash
# Build base image once (20-40 minutes)
./docker-build.sh base

# Build application quickly (2-5 minutes)
./docker-build.sh app

# Extract executables
./docker-build.sh extract
```

### Option 3: Docker Compose (Full environment)

```bash
# Build and run development environment
docker-compose up scifi-dev

# Or build base image for caching
docker-compose up scifi-base

# Or run production version
docker-compose up scifi-runtime
```

## 📁 Output Files

After building, you'll get:

```
docker-output/
├── SciFiDataScreen              # Linux executable
├── SciFiDataScreen.exe          # Windows executable (47MB)
└── start_scifi_datascreen.bat   # Windows launcher script
```

## 🔧 Build Commands Reference

| Command | Purpose | Time | Use Case |
|---------|---------|------|----------|
| `./docker-build.sh base` | Build MXE Qt5 base | 20-40 min | One-time setup |
| `./docker-build.sh app` | Build application | 2-5 min | Development |
| `./docker-build.sh full` | Build everything | 20-40 min | One-shot builds |
| `./docker-build.sh extract` | Get executables | <1 min | Deployment |
| `./docker-build.sh run` | Run container | <1 min | Testing |
| `./docker-build.sh clean` | Remove images | <1 min | Cleanup |

## 🐳 Dockerfile Variants

### `Dockerfile` - Complete Application
- Self-contained build including MXE Qt5
- Takes 20-40 minutes but no dependencies
- Good for CI/CD or one-time builds

### `Dockerfile.base` - Base Environment
- MXE Qt5 cross-compilation environment
- Build once, reuse many times
- Good for development workflow

### `docker-compose.yml` - Full Environment
- Multiple services (dev, base, runtime)
- Persistent volumes for caching
- Network configuration for UDP discovery

## 🌐 Network Configuration

The application uses UDP port 3250 for industrial module discovery:

```bash
# Expose UDP port when running manually
docker run -p 3250:3250/udp scifi-datascreen:latest

# Or use docker-compose (already configured)
docker-compose up scifi-runtime
```

## 🔄 Development Workflow

### Initial Setup
```bash
# Build base image (once)
./docker-build.sh base
```

### Regular Development
```bash
# Make changes to source code
vim src/mainwindow.cpp

# Rebuild application
./docker-build.sh app

# Extract new executables
./docker-build.sh extract

# Test Windows version
wine docker-output/SciFiDataScreen.exe  # If wine installed
```

### Production Deployment
```bash
# Copy files to target machines
scp docker-output/SciFiDataScreen user@linux-machine:/opt/scifi/
scp docker-output/SciFiDataScreen.exe user@windows-machine:C:/Tools/
scp docker-output/start_scifi_datascreen.bat user@windows-machine:C:/Tools/
```

## 🔍 Troubleshooting

### Build Issues

**Problem**: MXE build fails with "No space left on device"
```bash
# Solution: Clean Docker system
docker system prune -a
docker volume prune
```

**Problem**: Qt5 linking errors
```bash
# Solution: Rebuild base image
./docker-build.sh clean
./docker-build.sh base
```

**Problem**: libmodbus not found
```bash
# Solution: Check if MXE build completed
docker run --rm scifi-datascreen-base:latest ls -la /opt/libmodbus-windows/lib/
```

### Runtime Issues

**Problem**: UDP discovery not working
```bash
# Solution: Check port binding
docker run -p 3250:3250/udp --rm scifi-datascreen:latest netstat -ulnp
```

**Problem**: Windows executable won't run
```bash
# Solution: Check if it's properly cross-compiled
file docker-output/SciFiDataScreen.exe
# Should show: PE32+ executable (GUI) x86-64, for MS Windows
```

## 📊 Build Statistics

Typical build times and sizes:

| Component | Build Time | Image Size | Executable Size |
|-----------|------------|------------|----------------|
| MXE Base | 20-40 min | ~2.5 GB | - |
| Application | 2-5 min | ~100 MB | - |
| Linux binary | - | - | ~15 MB |
| Windows binary | - | - | ~47 MB |

## 🎛️ Environment Variables

| Variable | Default | Purpose |
|----------|---------|---------|
| `BUILD_TYPE` | Release | CMake build type |
| `MXE_TARGETS` | x86_64-w64-mingw32.static | Cross-compile target |
| `QT_QPA_PLATFORM` | - | Qt platform (use 'offscreen' for headless) |

## 🚀 Advanced Usage

### Custom Build Configuration

```bash
# Build with debug symbols
docker build --build-arg BUILD_TYPE=Debug -t scifi-debug .

# Build for different Windows architecture
docker build --build-arg MXE_TARGET=i686-w64-mingw32.static -t scifi-32bit .
```

### Integration with CI/CD

```yaml
# GitHub Actions example
- name: Build SciFi Data Screen
  run: |
    ./docker-build.sh full
    ./docker-build.sh extract
    
- name: Upload artifacts
  uses: actions/upload-artifact@v3
  with:
    name: scifi-executables
    path: docker-output/
```

### Multi-platform Support

```bash
# Build for ARM64 (if base image supports it)
docker buildx build --platform linux/arm64 -t scifi-arm64 .
```

## 📝 Notes

- Windows executable is **completely standalone** - no Qt5 installation needed on target
- Linux executable requires Qt5 libraries on target system
- UDP discovery works across network segments
- Modbus TCP tested with EPIC4 industrial modules
- Cross-compilation environment cached in base image for faster rebuilds

## 🔗 Related Files

- `Dockerfile` - Main application build
- `Dockerfile.base` - Cross-compilation base
- `docker-compose.yml` - Multi-service environment  
- `docker-build.sh` - Build automation script
- `CMakeLists.txt` - Build configuration
- `src/` - Application source code