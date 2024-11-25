cmake_minimum_required(VERSION 3.10)

project(lab1_rectangle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LIBRARY_SOURCES
    src/rectangle.cpp
    src/application.cpp
    src/input_handler.cpp
)

add_library(RectangleLib STATIC ${LIBRARY_SOURCES})

target_include_directories(RectangleLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(RectangleApp src/main.cpp)

target_link_libraries(RectangleApp PRIVATE RectangleLib)

find_package(SDL2 REQUIRED)
target_include_directories(RectangleLib PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(RectangleApp PRIVATE ${SDL2_LIBRARIES})
