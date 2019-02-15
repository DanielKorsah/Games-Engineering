cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Practical 1 ####
file(GLOB_RECURSE SOURCES practical_1/*.cpp practical_1/*.h)
add_executable(PRACTICAL_1 ${SOURCES})
target_include_directories(PRACTICAL_1 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_1 sfml-graphics)

#### Pong ####
file(GLOB_RECURSE SOURCES Pong/*.cpp Pong/*.h)
add_executable(Pong ${SOURCES})
target_include_directories(Pong PRIVATE ${SFML_INCS})
target_link_libraries(Pong sfml-graphics)

## Space invaders
file(GLOB_RECURSE SOURCES Invaders/*.cpp Invaders/*.h)
add_executable(Invaders ${SOURCES} )
target_include_directories(Invaders SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(Invaders sfml-graphics)

## Tile Engine
file(GLOB_RECURSE SOURCES TileEngine/*.cpp TileEngine/*.h)
add_executable(TileEngine ${SOURCES} )
target_include_directories(TileEngine PRIVATE ${SFML_INCS})
target_link_libraries(TileEngine sfml-graphics)

SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")

set_target_properties(Pong 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)

set_target_properties(Invaders 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)

set_target_properties(TileEngine
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)

add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)

add_dependencies(Pong copy_resources)
add_dependencies(Invaders copy_resources)
add_dependencies(TileEngine copy_resources)