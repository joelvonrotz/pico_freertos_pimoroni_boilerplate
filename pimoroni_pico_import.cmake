# This file can be dropped into a project to help locate the Pimoroni Pico libraries
# It will also set up the required include and module search paths.

set(PIMORONI_PICO_PATH $ENV{PIMORONI_PICO_PATH})
message("Using PIMORONI_PICO_PATH from environment ('${PIMORONI_PICO_PATH}')")


if(NOT IS_ABSOLUTE ${PIMORONI_PICO_PATH})
    get_filename_component(
        PIMORONI_PICO_PATH
        "${CMAKE_CURRENT_BINARY_DIR}/${PIMORONI_PICO_PATH}"
        ABSOLUTE)
endif()

if (NOT EXISTS ${PIMORONI_PICO_PATH})
    message(FATAL_ERROR "Directory '${PIMORONI_PICO_PATH}' not found")
endif ()

if (NOT EXISTS ${PIMORONI_PICO_PATH}/pimoroni_pico_import.cmake)
    message(FATAL_ERROR "Directory '${PIMORONI_PICO_PATH}' does not appear to contain the Pimoroni Pico libraries")
endif ()


set(PIMORONI_PICO_PATH ${PIMORONI_PICO_PATH} CACHE PATH "Path to the Pimoroni Pico libraries" FORCE)

include_directories(${PIMORONI_PICO_PATH})
list(APPEND CMAKE_MODULE_PATH ${PIMORONI_PICO_PATH})
