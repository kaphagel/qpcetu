# Professional Testing Framework for Industrial HMI
cmake_minimum_required(VERSION 3.16)
project(IndustrialHMI_Tests VERSION 1.0.0 LANGUAGES CXX)

# C++17 for optimal Qt5.15 compatibility
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Qt5 Testing Framework
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network Test)

# Enable automatic MOC for tests
set(CMAKE_AUTOMOC ON)

# Include parent source directory for testing
include_directories(${CMAKE_SOURCE_DIR}/src)

# Test output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

# Enable CTest for professional test runner integration
enable_testing()

# Common test libraries and dependencies
set(TEST_LIBRARIES
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
    Qt5::Test
)

# Include libmodbus for integration tests
if(WIN32)
    set(LIBMODBUS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/deps/windows/libmodbus-windows/src")
    set(LIBMODBUS_LIBRARY "${CMAKE_SOURCE_DIR}/deps/windows/libmodbus-windows/src/.libs/libmodbus.a")
    list(APPEND TEST_LIBRARIES ${LIBMODBUS_LIBRARY})
    include_directories(${LIBMODBUS_INCLUDE_DIR})
else()
    # Linux: Use bundled libmodbus from deps
    add_subdirectory(${CMAKE_SOURCE_DIR}/deps/external/libmodbus/src ${CMAKE_BINARY_DIR}/libmodbus)
    list(APPEND TEST_LIBRARIES libmodbus bsd)
endif()

# Mock Objects for Testing
add_library(TestMocks STATIC
    mocks/mockindustrialcontroller.h
    mocks/mockindustrialcontroller.cpp
    mocks/mockudpservice.h
    mocks/mockudpservice.cpp
    mocks/mockcontrollermanager.h
    mocks/mockcontrollermanager.cpp
)
target_link_libraries(TestMocks ${TEST_LIBRARIES})

# Unit Tests - Core Business Logic
add_executable(test_industrialcontroller
    unit/test_industrialcontroller.cpp
    ${CMAKE_SOURCE_DIR}/src/industrialcontroller.cpp
)
target_link_libraries(test_industrialcontroller ${TEST_LIBRARIES} TestMocks)
add_test(NAME UnitTest_IndustrialController COMMAND test_industrialcontroller)

# Test: UdpService Network Logic
add_executable(test_udpservice
    unit/test_udpservice.cpp
    ${CMAKE_SOURCE_DIR}/src/udpservice.cpp
)
target_link_libraries(test_udpservice ${TEST_LIBRARIES} TestMocks)
add_test(NAME UnitTest_UdpService COMMAND test_udpservice)

# Integration Tests - System Components
add_executable(test_udp_integration
    integration/test_udp_integration.cpp
    ${CMAKE_SOURCE_DIR}/src/udpservice.cpp
    ${CMAKE_SOURCE_DIR}/src/industrialcontroller.cpp
    ${CMAKE_SOURCE_DIR}/src/controllermanager.cpp
)
target_link_libraries(test_udp_integration ${TEST_LIBRARIES} TestMocks)
add_test(NAME IntegrationTest_UDP_Discovery COMMAND test_udp_integration)

# Test Configuration Summary
message(STATUS "===============================================")
message(STATUS "Professional Testing Framework Configuration")
message(STATUS "Unit Tests:        2 test suites")
message(STATUS "Integration Tests: 1 test suite") 
message(STATUS "Mock Objects:      3 mock classes")
message(STATUS "Test Framework:    Qt5::Test")
message(STATUS "===============================================")
