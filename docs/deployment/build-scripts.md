# Build Scripts

This directory contains the build scripts for the Quantum Tactical Processing Center - ETU project.

## Scripts Overview

### `build-linux.sh`
Cross-platform Linux build script using native GCC toolchain.
- **Output**: `../build-linux-x64/bin/ModernSciFiHMI`
- **Dependencies**: Qt5, CMake, build-essential
- **Platform**: Linux (native compilation)

### `build-windows.sh`
Cross-platform Windows build script using MXE (M cross environment).
- **Output**: `../build-windows-x64/bin/ModernSciFiHMI.exe`
- **Dependencies**: MXE toolchain, libmodbus-windows
- **Platform**: Windows x64 (cross-compilation from Linux)

### `build-all.sh`
Universal build script that builds both Linux and Windows versions sequentially.
- **Output**: Both Linux and Windows executables
- **Usage**: Single command to build all platforms

## Usage

```bash
# Build Linux version only
./build-linux.sh

# Build Windows version only  
./build-windows.sh

# Build both platforms
./build-all.sh
```

## Professional Build Structure

```
project-root/
├── scripts/                    # Build and automation scripts
│   ├── build-linux.sh
│   ├── build-windows.sh
│   └── build-all.sh
├── build-linux-x64/           # Linux build artifacts
│   └── bin/ModernSciFiHMI
├── build-windows-x64/         # Windows build artifacts
│   └── bin/ModernSciFiHMI.exe
└── src/                       # Source code
```

## Apple Design Integration

All builds include the enhanced Apple Human Interface Guidelines design system:
- Apple typography scale (Large Title, Title 1-3, Headline, Body, Callout, Subheadline, Footnote, Caption 1-2)
- Apple semantic colors (System Blue, System Green, System Red, etc.)
- Apple motion design principles
- Consistent touch-optimized interactions

## Build Verification

✅ **Linux Build**: Successfully tested (823KB executable)  
✅ **Windows Build**: Successfully tested (49MB standalone executable)  
✅ **Cross-Platform**: Both builds verified working with new structure