cmake_minimum_required(VERSION 3.10)
project(SDLGame)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)


add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})