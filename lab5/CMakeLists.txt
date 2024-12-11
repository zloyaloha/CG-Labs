cmake_minimum_required(VERSION 3.10)

project(RayTracingLab5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_policy(SET CMP0072 NEW)

set(SOURCES
    src/main.cpp
)

find_package(glfw3)
find_package(GLEW REQUIRED)
find_package(SFML 2.5 COMPONENTS window system REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system OpenGL::GL OpenGL::GLU GLEW::GLEW)