cmake_minimum_required(VERSION 3.16)
project(SciFiDataScreen VERSION 1.0.0 LANGUAGES CXX)

# C++17 is optimal for Qt5.15 - provides best template support
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Disable GNU extensions for portability

# Add tests
add_subdirectory(tests)

# Find Qt5 components
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network Svg)

# Enable automatic MOC (Meta-Object Compiler) and RCC (Resource Compiler)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)



# Add libmodbus as a subdirectory (from src)
add_subdirectory(external/libmodbus/src)


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

# Create executable
qt5_add_resources(ICON_RESOURCES resources/icons/overview.qrc)
add_executable(SciFiDataScreen ${SOURCES} ${HEADERS} ${ICON_RESOURCES})

# Link Qt and libmodbus libraries
target_link_libraries(SciFiDataScreen Qt5::Core Qt5::Widgets Qt5::Network Qt5::Svg libmodbus bsd)

# Set output directory
set_target_properties(SciFiDataScreen PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy any resources if needed (only if the directory exists)
if(EXISTS "${CMAKE_SOURCE_DIR}/resources")
    file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/)
endif()

# Mock service executable
add_executable(mockudpservice src/mockudpservice.cpp)
target_link_libraries(mockudpservice Qt5::Core Qt5::Network)
