cmake_minimum_required(VERSION 3# Header files (same as Linux version)
set(HEADERS
    ../src/mainwindow.h
    ../src/udpservice.h
    ../src/animatedprogressbar.h
    ../src/datawidget.h
    ../src/graphwidget.h
    ../src/industrialcontroller.h
    ../src/controllermanager.h
    ../src/pages/dashboardpage.h
    ../src/pages/graphspage.h
    ../src/pages/settingspage.h
    ../src/pages/udpresponsepage.h
    ../src/pages/overviewpage.h
    ../src/pages/dragdroppage_simple.h
    ../src/pages/controlleroverview.h
)ciFiDataScreen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# Qt5 components we need
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network Svg)

# Enable Qt5 MOC and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Source files (same as Linux version)
set(SOURCES
    ../src/main.cpp
    ../src/mainwindow.cpp
    ../src/udpservice.cpp
    ../src/animatedprogressbar.cpp
    ../src/datawidget.cpp
    ../src/graphwidget.cpp
    ../src/industrialcontroller.cpp
    ../src/controllermanager.cpp
    ../src/pages/dashboardpage.cpp
    ../src/pages/graphspage.cpp
    ../src/pages/settingspage.cpp
    ../src/pages/udpresponsepage.cpp
    ../src/pages/overviewpage.cpp
    ../src/pages/dragdroppage_simple.cpp
    ../src/pages/controlleroverview.cpp
    # Architecture Pattern Implementations
    ../src/strategies/controllerstrategy.cpp
    ../src/commands/command.cpp
    ../src/statemachine/controllerstatemachine.cpp
)

# Header files for MOC
set(HEADERS
    ../src/mainwindow.h
    ../src/udpservice.h
    ../src/animatedprogressbar.h
    ../src/datawidget.h
    ../src/graphwidget.h
    ../src/pages/dashboardpage.h
    ../src/pages/graphspage.h
    ../src/pages/settingspage.h
    ../src/pages/udpresponsepage.h
    ../src/pages/overviewpage.h
    ../src/pages/dragdroppage_simple.h
)

# Add Qt resources for icons
qt5_add_resources(ICON_RESOURCES ../resources/icons/overview.qrc)

# Create the executable
add_executable(SciFiDataScreen ${SOURCES} ${HEADERS} ${ICON_RESOURCES})

# Link Qt5 libraries
target_link_libraries(SciFiDataScreen 
    Qt5::Core 
    Qt5::Widgets 
    Qt5::Network 
    Qt5::Svg
)

# Windows specific settings
if(WIN32 OR MINGW)
    # Link Windows networking libraries and libmodbus
    target_link_libraries(SciFiDataScreen 
        ws2_32 
        iphlpapi
        /workspaces/qpcetu/libmodbus-windows-install/lib/libmodbus.a
    )
    
    # Static linking for standalone executable
    set_target_properties(SciFiDataScreen PROPERTIES
        LINK_FLAGS "-static -static-libgcc -static-libstdc++"
    )
    
    # Windows app (not console)
    set_target_properties(SciFiDataScreen PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Include directories
target_include_directories(SciFiDataScreen PRIVATE 
    ../src
    /workspaces/qpcetu/libmodbus-windows-install/include
)