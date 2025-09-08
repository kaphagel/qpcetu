cmake_minimum_required(VERSION 3.16)
project(SciFiDataScreen VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt5 components
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

# Enable automatic MOC (Meta-Object Compiler)
set(CMAKE_AUTOMOC ON)

# Find and configure libmodbus
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBMODBUS REQUIRED libmodbus)
include_directories(${LIBMODBUS_INCLUDE_DIRS})
link_directories(${LIBMODBUS_LIBRARY_DIRS})

# Source files
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/datawidget.cpp
    src/animatedprogressbar.cpp
    src/graphwidget.cpp
)

# Header files
set(HEADERS
    src/mainwindow.h
    src/datawidget.h
    src/animatedprogressbar.h
    src/graphwidget.h
)

# Create executable
add_executable(SciFiDataScreen ${SOURCES} ${HEADERS})

# Link Qt and libmodbus libraries
target_link_libraries(SciFiDataScreen Qt5::Core Qt5::Widgets ${LIBMODBUS_LIBRARIES})

# Set output directory
set_target_properties(SciFiDataScreen PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy any resources if needed (only if the directory exists)
if(EXISTS "${CMAKE_SOURCE_DIR}/resources")
    file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/)
endif()
