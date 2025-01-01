cmake_minimum_required(VERSION 3.10)
project(imglib)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SOURCES

)

set(HEADERS
    include/imglib.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(modules/imgcodecs)
add_subdirectory(modules/core)
add_subdirectory(modules/highgui)

add_executable(read_pbm_file examples/read_pbm_file.c)
target_link_libraries(read_pbm_file PRIVATE core imgcodecs highgui)

add_library(imglib INTERFACE)
target_link_libraries(imglib INTERFACE core imgcodecs highgui)





