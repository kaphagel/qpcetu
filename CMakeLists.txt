cmake_minimum_required(VERSION 3.16)
project(SciFiDataScreen VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add tests
add_subdirectory(tests)

# Find Qt5 components
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network)

# Enable automatic MOC (Meta-Object Compiler)
set(CMAKE_AUTOMOC ON)



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
    src/pages/dashboardpage.cpp
    src/pages/graphspage.cpp
    src/pages/settingspage.cpp
    src/pages/udpresponsepage.cpp
)

# Header files
set(HEADERS
    src/mainwindow.h
    src/datawidget.h
    src/animatedprogressbar.h
    src/graphwidget.h
    src/udpservice.h
    src/pages/dashboardpage.h
    src/pages/graphspage.h
    src/pages/settingspage.h
    src/pages/udpresponsepage.h
)

# Create executable
add_executable(SciFiDataScreen ${SOURCES} ${HEADERS})

# Link Qt and libmodbus libraries
target_link_libraries(SciFiDataScreen Qt5::Core Qt5::Widgets Qt5::Network libmodbus)

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
