cmake_minimum_required(VERSION 2.8)
project(SOT)

# Build release if no build type has been specified
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "NOTE: No build type specified")
    set(CMAKE_BUILD_TYPE Release)
endif()

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Debug build.")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
    message(STATUS "Release build.")
ELSE()
    message(STATUS "Some other build type.")
ENDIF()

set(CMAKE_MACOSX_RPATH 1)

# The version number.
set (SOT_VERSION_MAJOR 0)
set (SOT_VERSION_MINOR 10)

include_directories(include)

# Move header files
file(GLOB MAIN_HEADER "include/sot.h")
install(FILES ${MAIN_HEADER} DESTINATION include)
file(GLOB BITS_HEADERS "include/sot_bits/*.h")
install(FILES ${BITS_HEADERS} DESTINATION include/sot_bits)

