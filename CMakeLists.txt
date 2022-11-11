cmake_minimum_required(VERSION 3.23)
project(Assedik C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(SDL2_INCLUDE_DIR ./include/SDL2)
set(SDL2_LIB_DIR ./lib)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
FILE(GLOB Include include/*.h)
FILE(GLOB Sources src/*.c)
add_executable(Assedik ${Sources} ${Include})
target_link_libraries(${PROJECT_NAME} SDL2main SDL2)

