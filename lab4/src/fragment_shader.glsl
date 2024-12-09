#version 330 core

in vec3 Normal;    // Нормаль поверхности
in vec3 FragPos;       // Позиция фрагмента

out vec4 FragColor;   // Цвет пикселя

uniform vec3 lightPos; // Позиция источника света
uniform vec3 lightColor; // Цвет света
uniform vec3 objectColor; // Цвет объекта
uniform int objType; // 0 - источник, 1 - объект
uniform vec3 lightDir; // 0 - источник, 1 - объект

void main()
{
    if (objType == 1) {
        vec3 norm = normalize(Normal);
        vec3 lightDirNormalized = normalize(-lightDir);
        float diff = max(dot(norm, lightDirNormalized), 0.1);
        
        vec3 diffuse = diff * lightColor * objectColor;
        
        FragColor = vec4(diffuse, 1.0);  // Возвращаем результат
    } 
    if (objType == 0) {
        FragColor = vec4(objectColor, 1.0);   
    }
}
