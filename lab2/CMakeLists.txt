cmake_minimum_required(VERSION 3.10)

# Имя проекта
project(StaticCubeExample)

# Версия стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем исходные файлы
set(SOURCES
    src/main.cpp
    src/object.cpp
    src/command_handler.cpp
    src/app.cpp
)

# Указываем зависимости: SFML и OpenGL
find_package(glfw3)
find_package(SFML 2.5 COMPONENTS window system REQUIRED)
find_package(OpenGL REQUIRED)

# Добавляем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

# Линкуем SFML и OpenGL
target_link_libraries(${PROJECT_NAME} sfml-window sfml-system OpenGL::GL OpenGL::GLU)
