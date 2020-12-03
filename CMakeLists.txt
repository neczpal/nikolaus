cmake_minimum_required(VERSION 3.10)
project(Nikolaus)

set(CMAKE_C_STANDARD 99)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_GFX_INCLUDE_DIRS})

set(GAME_SOURCES
        src/graphics.c
        src/graphics.h
        src/main.c
        src/maps.c
        src/maps.h
        src/scores.c
        src/scores.h
        src/utils.c
        src/utils.h)

set(MAPGEN_SOURCES
        src/map_gen.c
        src/map_gen.h)

add_executable(Nikolaus
        ${GAME_SOURCES})

add_executable(MapGen
        ${MAPGEN_SOURCES})


#COPY MAPS
add_custom_command(
        TARGET Nikolaus POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/res/maps/*.txt
        ${CMAKE_CURRENT_BINARY_DIR}/)

#COPY IMAGES
add_custom_command(
        TARGET Nikolaus POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/res/imgs/*.png
        ${CMAKE_CURRENT_BINARY_DIR}/)

target_link_libraries(Nikolaus ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_GFX_LIBRARIES})
