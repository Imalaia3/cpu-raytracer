cmake_minimum_required(VERSION 3.7)
project(CPURaytracer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(Raytracer ${SOURCES})

find_package(SDL2 REQUIRED)
include_directories(Raytracer ${SDL2_INCLUDE_DIRS})
target_link_libraries(Raytracer PRIVATE ${SDL2_LIBRARIES}) # if not PRIVATE, cmake complains.

# TODO: Implement FetchContent
find_package(glm CONFIG REQUIRED)
target_link_libraries(Raytracer PRIVATE glm::glm)