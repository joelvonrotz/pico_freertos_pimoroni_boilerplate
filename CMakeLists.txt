cmake_minimum_required(VERSION 3.12)

# Change your executable name to something creative!
set(NAME pico-freertos-stellar) # <-- Name your project/executable here!
set(ENV{PICO_BOARD} pico_w)

include(pimoroni_pico_import.cmake)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Gooey boilerplate
project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

include_directories(
    inc
)

add_subdirectory($ENV{FREERTOS_PATH} freertos)


# Add your source files
add_executable(${NAME}
    main.cpp # <-- Add source files here!
)

include(libraries/pico_graphics/pico_graphics)
include(libraries/stellar_unicorn/stellar_unicorn)

# Don't forget to link the libraries you need!
target_link_libraries(${NAME}
    pico_stdlib
    hardware_pio
    hardware_adc
    hardware_dma
    pico_graphics
    stellar_unicorn
    freertos
)

# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})
