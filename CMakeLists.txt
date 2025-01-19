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

add_executable(read_pbm_file examples/debug/read_pbm_file.c)
target_link_libraries(read_pbm_file PRIVATE core imgcodecs highgui)

add_executable(pixel_display examples/debug/pixel_display.c)
target_link_libraries(pixel_display PRIVATE core imgcodecs highgui)

add_executable(p4_pbm_display examples/debug/p4_pbm_display.c)
target_link_libraries(p4_pbm_display PRIVATE core imgcodecs highgui)

add_executable(p4_pbm_comment examples/debug/p4_pbm_comment.c)
target_link_libraries(p4_pbm_comment PRIVATE core imgcodecs highgui)

add_executable(display_loop examples/debug/display_loop.c)
target_link_libraries(display_loop PRIVATE core imgcodecs highgui)

add_executable(display_pgm_P2 examples/debug/display_pgm_P2.c)
target_link_libraries(display_pgm_P2 PRIVATE core imgcodecs highgui)

add_executable(display_pgm_P5 examples/debug/display_pgm_P5.c)
target_link_libraries(display_pgm_P5 PRIVATE core imgcodecs highgui)

add_executable(read_pgm_file examples/debug/read_pgm_file.c)
target_link_libraries(read_pgm_file PRIVATE core imgcodecs highgui)


add_library(imglib INTERFACE)
target_link_libraries(imglib INTERFACE core imgcodecs highgui)





