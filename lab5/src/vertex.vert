#version 450 core

layout(location = 0) in vec3 inPosition;  // Входная позиция вершины
layout(location = 1) in vec3 inColor;     // Входной цвет вершины

out vec3 fragColor;  // Цвет, передаваемый в фрагментный шейдер

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Преобразуем вершину с помощью матриц модели, вида и проекции
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
    fragColor = inColor;  // Передаем цвет в фрагментный шейдер
}
