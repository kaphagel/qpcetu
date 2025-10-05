cmake_minimum_required(VERSION 3.16)
project(libmodbus)

set(SOURCES
    modbus.c
    modbus-data.c
    modbus-rtu.c
    modbus-tcp.c
)

add_library(libmodbus STATIC ${SOURCES})

# Include headers for consumers
set_target_properties(libmodbus PROPERTIES PUBLIC_HEADER "modbus.h;modbus-rtu.h;modbus-tcp.h")
target_include_directories(libmodbus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Ensure netinet/ip.h is available for IPTOS_LOWDELAY
target_compile_definitions(libmodbus PRIVATE _GNU_SOURCE)
