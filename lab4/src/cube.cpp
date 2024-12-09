#include "cube.h"

Cube::Cube(float size) : size(size) {
    setupCube(); // Настроить данные куба
}

void Cube::setupCube() {
    objColor = glm::vec3(1.0, 0.5, 0);

    float half = size / 2.0f;
    
    // Вершины куба (8 угловых вершин)
    glm::vec3 vertices[] = {
        glm::vec3(-half, -half, -half),  // 0
        glm::vec3( half, -half, -half),  // 1
        glm::vec3( half,  half, -half),  // 2
        glm::vec3(-half,  half, -half),  // 3
        glm::vec3(-half, -half,  half),  // 4
        glm::vec3( half, -half,  half),  // 5
        glm::vec3( half,  half,  half),  // 6
        glm::vec3(-half,  half,  half)   // 7
    };

    glm::vec3 vertexData[] = {
    // Задняя грань (нормаль по оси Z)
    // Первый треугольник
    vertices[0], glm::vec3(0.0f, 0.0f, -1.0f),
    vertices[1], glm::vec3(0.0f, 0.0f, -1.0f),
    vertices[2], glm::vec3(0.0f, 0.0f, -1.0f),
    // Второй треугольник
    vertices[2], glm::vec3(0.0f, 0.0f, -1.0f),
    vertices[3], glm::vec3(0.0f, 0.0f, -1.0f),
    vertices[0], glm::vec3(0.0f, 0.0f, -1.0f),

    // Левая грань (нормаль по оси X)
    // Первый треугольник
    vertices[0], glm::vec3(-1.0f, 0.0f, 0.0f),
    vertices[3], glm::vec3(-1.0f, 0.0f, 0.0f),
    vertices[7], glm::vec3(-1.0f, 0.0f, 0.0f),
    // Второй треугольник
    vertices[7], glm::vec3(-1.0f, 0.0f, 0.0f),
    vertices[4], glm::vec3(-1.0f, 0.0f, 0.0f),
    vertices[0], glm::vec3(-1.0f, 0.0f, 0.0f),

    // Правая грань (нормаль по оси X)
    // Первый треугольник
    vertices[1], glm::vec3(1.0f, 0.0f, 0.0f),
    vertices[2], glm::vec3(1.0f, 0.0f, 0.0f),
    vertices[6], glm::vec3(1.0f, 0.0f, 0.0f),
    // Второй треугольник
    vertices[6], glm::vec3(1.0f, 0.0f, 0.0f),
    vertices[5], glm::vec3(1.0f, 0.0f, 0.0f),
    vertices[1], glm::vec3(1.0f, 0.0f, 0.0f),

    // Нижняя грань (нормаль по оси Y)
    // Первый треугольник
    vertices[0], glm::vec3(0.0f, -1.0f, 0.0f),
    vertices[1], glm::vec3(0.0f, -1.0f, 0.0f),
    vertices[5], glm::vec3(0.0f, -1.0f, 0.0f),
    // Второй треугольник
    vertices[5], glm::vec3(0.0f, -1.0f, 0.0f),
    vertices[4], glm::vec3(0.0f, -1.0f, 0.0f),
    vertices[0], glm::vec3(0.0f, -1.0f, 0.0f),

    // Верхняя грань (нормаль по оси Y)
    // Первый треугольник
    vertices[3], glm::vec3(0.0f, 1.0f, 0.0f),
    vertices[2], glm::vec3(0.0f, 1.0f, 0.0f),
    vertices[6], glm::vec3(0.0f, 1.0f, 0.0f),
    // Второй треугольник
    vertices[6], glm::vec3(0.0f, 1.0f, 0.0f),
    vertices[7], glm::vec3(0.0f, 1.0f, 0.0f),
    vertices[3], glm::vec3(0.0f, 1.0f, 0.0f),

    // Передняя грань (нормаль по оси Z)
    // Первый треугольник
    vertices[4], glm::vec3(0.0f, 0.0f, 1.0f),
    vertices[5], glm::vec3(0.0f, 0.0f, 1.0f),
    vertices[6], glm::vec3(0.0f, 0.0f, 1.0f),
    // Второй треугольник
    vertices[6], glm::vec3(0.0f, 0.0f, 1.0f),
    vertices[7], glm::vec3(0.0f, 0.0f, 1.0f),
    vertices[4], glm::vec3(0.0f, 0.0f, 1.0f)
};

    // Создаем VAO и VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData[0], GL_STATIC_DRAW);

    // Устанавливаем атрибуты для грани
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Устанавливаем атрибуты для нормали (aNormal)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Cube::setShaderProgram(GLuint program) {
    shaderProgram = program;
}

void Cube::setUniforms(const glm::mat4& view, const glm::mat4& projection, const Light& light, int type) {
    glUseProgram(shaderProgram);

    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    GLint lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
    GLint lightDirLoc = glGetUniformLocation(shaderProgram, "lightDir");
    GLint lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
    GLint objectColorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    GLint objectTypeLoc = glGetUniformLocation(shaderProgram, "objType");

    glm::mat4 model = glm::mat4(1.0f);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glUniform3fv(lightPosLoc, 1, glm::value_ptr(light.position));
    glUniform3fv(lightDirLoc, 1, glm::value_ptr(light.dir));
    glUniform3fv(lightColorLoc, 1, glm::value_ptr(light.color));
    glUniform3fv(objectColorLoc, 1, glm::value_ptr(objColor));
    glUniform1i(objectTypeLoc, type);
}

void Cube::draw(const glm::mat4& view, const glm::mat4& projection, const Light& light) {
    glUseProgram(shaderProgram);

    // Отрисовка основного куба
    setUniforms(view, projection, light, 1); // Устанавливаем все нужные uniform-переменные
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36); // Рисуем 36 вершин для 6 граней куба
    glBindVertexArray(0);

    // Отрисовка светового куба
    glm::mat4 model = glm::translate(glm::mat4(1.0f), light.position); // Позиция света
    model = glm::scale(model, glm::vec3(0.2f)); // Уменьшаем размер светового куба

    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    GLint objectColorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    GLint objectTypeLoc = glGetUniformLocation(shaderProgram, "objType");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3fv(objectColorLoc, 1, glm::value_ptr(light.color)); // Световой куб имеет цвет света
    glUniform1i(objectTypeLoc, 0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    // Отрисовка линии направления света
    glm::vec3 lineVertices[2] = {
        light.position,                       // Начало линии (точно центр куба)
        light.position + light.dir // Конец линии (длина 2.0)
    };

    GLuint lineVBO, lineVAO;
    glGenVertexArrays(1, &lineVAO);
    glGenBuffers(1, &lineVBO);

    glBindVertexArray(lineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glUniform1i(objectTypeLoc, 0); // Тип объекта — линия
    glBindVertexArray(lineVAO);
    glDrawArrays(GL_LINES, 0, 2); // Рисуем линию
    glBindVertexArray(0);

    // Очистка ресурсов для линии
    glDeleteVertexArrays(1, &lineVAO);
    glDeleteBuffers(1, &lineVBO);
}

