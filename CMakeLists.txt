cmake_minimum_required(VERSION 3.16)
project(SciFiDataScreen VERSION 1.0.0 LANGUAGES CXX)

# C++17 is optimal for Qt5.15 - provides best template support
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Disable GNU extensions for portability

# MXE Cross-compilation setup for Windows
if(WIN32 AND CMAKE_CROSSCOMPILING)
    # Set MXE installation path
    set(MXE_ROOT "${CMAKE_SOURCE_DIR}/deps/toolchain/mxe-lite")
    set(MXE_TARGET_PREFIX "${MXE_ROOT}/usr/x86_64-w64-mingw32.static")
    
    # Add MXE to CMAKE_PREFIX_PATH
    set(CMAKE_PREFIX_PATH "${MXE_TARGET_PREFIX}" ${CMAKE_PREFIX_PATH})
    
    # Set find root paths
    set(CMAKE_FIND_ROOT_PATH "${MXE_TARGET_PREFIX}")
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    
    # Set compilers
    set(CMAKE_C_COMPILER "${MXE_ROOT}/usr/bin/x86_64-w64-mingw32.static-gcc")
    set(CMAKE_CXX_COMPILER "${MXE_ROOT}/usr/bin/x86_64-w64-mingw32.static-g++")
    set(CMAKE_RC_COMPILER "${MXE_ROOT}/usr/bin/x86_64-w64-mingw32.static-windres")
    
    message(STATUS "Using MXE cross-compilation toolchain at: ${MXE_ROOT}")
endif()

# Tests are now integrated in the main build system
# add_subdirectory(tests)

# Find Qt5 components
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network Svg)

# Enable automatic MOC (Meta-Object Compiler) and RCC (Resource Compiler)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Platform-specific libmodbus handling
if(WIN32)
    # Use Windows-compatible libmodbus from deps structure
    message(STATUS "Windows build - using deps/windows/libmodbus-windows")
    set(LIBMODBUS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/deps/windows/libmodbus-windows/src")
    set(LIBMODBUS_LIBRARY "${CMAKE_SOURCE_DIR}/deps/windows/libmodbus-windows/src/.libs/libmodbus.a")
else()
    # Add libmodbus as a subdirectory (from deps/external) for Linux/Unix
    add_subdirectory(deps/external/libmodbus/src)
    set(LIBMODBUS_INCLUDE_DIR "")
    set(LIBMODBUS_LIBRARY "libmodbus")
endif()


# Source files
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/datawidget.cpp
    src/animatedprogressbar.cpp
    src/graphwidget.cpp
    src/udpservice.cpp
    src/industrialcontroller.cpp
    src/controllermanager.cpp
    src/pages/dashboardpage.cpp
    src/pages/graphspage.cpp
    src/pages/settingspage.cpp
    src/pages/udpresponsepage.cpp
    src/pages/overviewpage.cpp
    src/pages/dragdroppage_simple.cpp
    src/pages/controlleroverview.cpp
    # Architecture Pattern Implementations
    src/strategies/controllerstrategy.cpp
    src/commands/command.cpp
    src/statemachine/controllerstatemachine.cpp
)

# Header files
set(HEADERS
    src/mainwindow.h
    src/datawidget.h
    src/animatedprogressbar.h
    src/graphwidget.h
    src/udpservice.h
    src/industrialcontroller.h
    src/controllermanager.h
    src/pages/dashboardpage.h
    src/pages/graphspage.h
    src/pages/settingspage.h
    src/pages/udpresponsepage.h
    src/pages/dragdroppage_simple.h
    src/pages/controlleroverview.h
    # Architecture Pattern Headers
    src/strategies/controllerstrategy.h
    src/commands/command.h
    src/statemachine/controllerstatemachine.h
)

# Create executable - Traditional HMI (commented out - building only touch-optimized version)
qt5_add_resources(ICON_RESOURCES resources/icons/overview.qrc)
# if(WIN32)
#     add_executable(SciFiDataScreen WIN32 ${SOURCES} ${HEADERS} ${ICON_RESOURCES})
# else()
#     add_executable(SciFiDataScreen ${SOURCES} ${HEADERS} ${ICON_RESOURCES})
# endif()

# Add include directories for Windows libmodbus
# if(WIN32)
#     target_include_directories(SciFiDataScreen PRIVATE ${LIBMODBUS_INCLUDE_DIR})
# endif()

# Create modern HMI executable
set(MODERN_SOURCES
    src/main_modern.cpp
    src/udpservice.cpp
    src/industrialcontroller.cpp
    src/controllermanager.cpp
    src/pages/dashboardpage.cpp
    src/pages/graphspage.cpp
    src/pages/settingspage.cpp
    src/pages/udpresponsepage.cpp
    src/pages/overviewpage.cpp
    src/pages/simpledragdroppage.cpp
    # Original widget dependencies
    src/mainwindow.cpp
    src/datawidget.cpp
    src/animatedprogressbar.cpp
    src/graphwidget.cpp
    # Modern UI Components
    src/ui/modernmainwindow.cpp
    src/ui/controllercardwidget.cpp
    src/ui/thememanager.cpp
    src/ui/themesettingswidget.cpp
    src/ui/applestyle.cpp
    # Architecture Pattern Implementations
    src/strategies/controllerstrategy.cpp
    src/commands/command.cpp
    src/statemachine/controllerstatemachine.cpp
)

if(WIN32)
    add_executable(ModernSciFiHMI WIN32 ${MODERN_SOURCES} ${ICON_RESOURCES})
else()
    add_executable(ModernSciFiHMI ${MODERN_SOURCES} ${ICON_RESOURCES})
endif()

# Add include directories for Windows libmodbus
if(WIN32)
    target_include_directories(ModernSciFiHMI PRIVATE ${LIBMODBUS_INCLUDE_DIR})
endif()

# Link Qt and libmodbus libraries - Only for touch-optimized ModernSciFiHMI
if(WIN32)
    # target_link_libraries(SciFiDataScreen Qt5::Core Qt5::Widgets Qt5::Network Qt5::Svg ${LIBMODBUS_LIBRARY})
    target_link_libraries(ModernSciFiHMI Qt5::Core Qt5::Widgets Qt5::Network Qt5::Svg ${LIBMODBUS_LIBRARY})
else()
    # target_link_libraries(SciFiDataScreen Qt5::Core Qt5::Widgets Qt5::Network Qt5::Svg libmodbus bsd)
    target_link_libraries(ModernSciFiHMI Qt5::Core Qt5::Widgets Qt5::Network Qt5::Svg libmodbus bsd)
endif()

# Set output directory - Only for touch-optimized ModernSciFiHMI
# set_target_properties(SciFiDataScreen PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
# )
set_target_properties(ModernSciFiHMI PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy any resources if needed (only if the directory exists)
if(EXISTS "${CMAKE_SOURCE_DIR}/resources")
    file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/)
endif()

# Mock service executable
add_executable(mockudpservice src/mockudpservice.cpp)
target_link_libraries(mockudpservice Qt5::Core Qt5::Network)
