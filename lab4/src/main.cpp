#include "cube.h"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <fstream>
#include <iostream>

std::string ReadShaderFile(const char* filepath) {
    std::ifstream file(filepath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void handleInput(glm::vec3& lightDirection) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        lightDirection.x -= 0.01f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        lightDirection.x += 0.01f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        lightDirection.y += 0.01f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        lightDirection.y -= 0.01f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        lightDirection.z -= 0.01f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        lightDirection.z += 0.01f;
    }
}

GLuint compileShader(GLenum shaderType, const std::string& shaderSource) {
    GLuint shader = glCreateShader(shaderType);
    const char* src = shaderSource.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
    }

    return shader;
}

GLuint createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Program linking failed: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main() {
    sf::Window window(sf::VideoMode(800, 600), "3D Cube with Lighting", sf::Style::Close | sf::Style::Resize);
    window.setActive(true);

    glewInit();

    std::string vertexShaderSource = ReadShaderFile("../src/vertex_shader.glsl");
    std::string fragmentShaderSource = ReadShaderFile("../src/fragment_shader.glsl");

    GLuint shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

    Cube cube(1.0f);
    cube.setShaderProgram(shaderProgram);

    glm::mat4 view = glm::lookAt(glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    Light light;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Черный цвет
    light.color = glm::vec3(0.0f, 1.0f, 1.0f);
    glm::vec3 cube_position = glm::vec3(0.0f, 0.0f, 0.0f);
    light.position = glm::vec3(0.0f, 0.0f, 2.0f);
    light.dir = cube_position - light.position;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        handleInput(light.dir);
        std::cout << light.dir.x << ' ' << light.dir.y << ' ' << light.dir.z << std::endl;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        // Вызов функции отрисовки куба
        cube.draw(view, projection, light);

        window.display();  // Отображаем кадр
    }

    return 0;
}
