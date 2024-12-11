#version 450 core

in vec3 fragColor;  // Цвет, полученный из вершинного шейдера
out vec4 color;     // Выходной цвет пикселя

void main() {
    // Просто возвращаем цвет, полученный из вершинного шейдера
    color = vec4(fragColor, 1.0);
}
