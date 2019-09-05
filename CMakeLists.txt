cmake_minimum_required(VERSION 3.10)
project(nextcom C)
#
set(CMAKE_C_STANDARD 11)
#
include_directories(
        /u/ZX/z88dk/include/_DEVELOPMENT/sccz80
)

add_executable(nextcom
# MAIN RAM
        src/nextcom
        src/dispatch
        src/inc/ascii
        src/hardware/init
        src/hardware/uart
        src/hardware/ula
        src/hardware/tilemap
        src/modules/terminal
        )
