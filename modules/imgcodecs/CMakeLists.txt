cmake_minimum_required(VERSION 3.10)
project(imgcodecs)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SOURCES
    imgcodecs_utils.c

    read.c
    read_pxm.c

    write.c
    write_pxm.c

)

set(HEADERS
    include/imgcodecs.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC core)

