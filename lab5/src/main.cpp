#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

const GLuint WIDTH = 1080, HEIGHT = 720;

struct UniformLocations {
    GLint sphereCenter[2];
    GLint sphereRadius[2];
    GLint sphereMaterialAmbient[2];
    GLint sphereMaterialDiffuse[2];
    GLint sphereMaterialSpecular[2];
    GLint sphereMaterialShininess[2];
    GLint sphereMaterialReflection[2];
    GLint planePoint;
    GLint planeNormal;
    GLint planeMaterialAmbient;
    GLint planeMaterialDiffuse;
    GLint planeMaterialShininess;
    GLint planeMaterialReflection;
    GLint cameraPos;
    GLint lightPos;
    GLint lightColor;
    GLint spheresCount;
};

UniformLocations locations;

void getUniformLocations(const GLuint& computeProgram) {
    for (int i = 0; i < 2; ++i) {
        locations.sphereCenter[i] = glGetUniformLocation(computeProgram, ("spheres[" + std::to_string(i) + "].center").c_str());
        locations.sphereRadius[i] = glGetUniformLocation(computeProgram, ("spheres[" + std::to_string(i) + "].radius").c_str());
        locations.sphereMaterialAmbient[i] = glGetUniformLocation(computeProgram, ("spheres[" + std::to_string(i) + "].material.ambient").c_str());
        locations.sphereMaterialDiffuse[i] = glGetUniformLocation(computeProgram, ("spheres[" + std::to_string(i) + "].material.diffuse").c_str());
        locations.sphereMaterialSpecular[i] = glGetUniformLocation(computeProgram, ("spheres[" + std::to_string(i) + "].material.specular").c_str());
        locations.sphereMaterialShininess[i] = glGetUniformLocation(computeProgram, ("spheres[" + std::to_string(i) + "].material.shininess").c_str());
        locations.sphereMaterialReflection[i] = glGetUniformLocation(computeProgram, ("spheres[" + std::to_string(i) + "].material.reflection").c_str());
    }

    locations.planePoint = glGetUniformLocation(computeProgram, "uPlane.point");
    locations.planeNormal = glGetUniformLocation(computeProgram, "uPlane.normal");
    locations.planeMaterialAmbient = glGetUniformLocation(computeProgram, "uPlane.material.ambient");
    locations.planeMaterialDiffuse = glGetUniformLocation(computeProgram, "uPlane.material.diffuse");
    locations.planeMaterialShininess = glGetUniformLocation(computeProgram, "uPlane.material.shininess");
    locations.planeMaterialReflection = glGetUniformLocation(computeProgram, "uPlane.material.reflection");
    locations.cameraPos = glGetUniformLocation(computeProgram, "uCameraPos");
    locations.lightPos = glGetUniformLocation(computeProgram, "uLight.position");
    locations.lightColor = glGetUniformLocation(computeProgram, "uLight.color");
    locations.spheresCount = glGetUniformLocation(computeProgram, "spheresCount");
}

std::string ReadShaderFile(const char* filepath) {
    std::ifstream file(filepath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    float reflection;
};

struct Sphere {
    float radius;
    glm::vec3 center;
    Material material;
};

struct Plane {
    glm::vec3 point;
    glm::vec3 normal;
    Material material;
};

struct Light {
    glm::vec3 position;
    glm::vec3 color;
};

void handleInput(glm::vec3& cameraPos) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        cameraPos.x -= 0.2f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        cameraPos.x += 0.2f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        cameraPos.y = std::clamp(cameraPos.y + 0.2f, 0.2f, std::numeric_limits<float>::max());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        cameraPos.y = std::clamp(cameraPos.y - 0.2f, 0.2f, std::numeric_limits<float>::max());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        cameraPos.z -= 0.2f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        cameraPos.z += 0.2f;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Compute Shader Example", sf::Style::Default, sf::ContextSettings(24));

    if (glewInit() != GLEW_OK) {
        std::cerr << "Ошибка инициализации GLEW!" << std::endl;
        return -1;
    }

    GLuint tex_output;
    glGenTextures(1, &tex_output);
    glBindTexture(GL_TEXTURE_2D, tex_output);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, nullptr);
    glBindImageTexture(0, tex_output, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

    std::string computeShaderSourceString = ReadShaderFile("../src/compute.comp");
    const char * computeShaderSource = computeShaderSourceString.c_str();
    GLuint computeShader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(computeShader, 1, &computeShaderSource, nullptr);
    glCompileShader(computeShader);

    GLint success;
    glGetShaderiv(computeShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(computeShader, 512, nullptr, infoLog);
        std::cerr << "Ошибка компиляции compute шейдера: " << infoLog << std::endl;
        return -1;
    }

    GLuint computeProgram = glCreateProgram();
    glAttachShader(computeProgram, computeShader);
    glLinkProgram(computeProgram);

    GLuint quadVAO, quadVBO;
    GLfloat quadVertices[] = {
        // Координаты        // Текстурные координаты
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,

        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);

    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    GLuint quadProgram;
    const char* quadVertexShaderSource = R"(
        #version 450 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec2 texCoords;
        out vec2 TexCoords;
        void main() {
            gl_Position = vec4(position, 1.0);
            TexCoords = texCoords;
        }
    )";

    const char* quadFragmentShaderSource = R"(
        #version 450 core
        out vec4 color;
        in vec2 TexCoords;
        uniform sampler2D texture1;
        void main() {
            color = texture(texture1, TexCoords);
        }
    )";

    GLuint quadVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(quadVertexShader, 1, &quadVertexShaderSource, nullptr);
    glCompileShader(quadVertexShader);

    GLuint quadFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(quadFragmentShader, 1, &quadFragmentShaderSource, nullptr);
    glCompileShader(quadFragmentShader);

    glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 5.0f);
    quadProgram = glCreateProgram();
    glAttachShader(quadProgram, quadVertexShader);
    glAttachShader(quadProgram, quadFragmentShader);
    glLinkProgram(quadProgram);
    float i = 0;
    getUniformLocations(computeProgram);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Запуск compute шейдера
        glUseProgram(computeProgram);
        std::vector<Sphere> spheres = {
            { 1.0f, glm::vec3(0.0f, 3.0f, -1.0f), {glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.5}},
            { 1.0f, glm::vec3(2.0f, 5.0f, -3.0f), {glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.9}}
        };

        Plane plane;
        plane.point = glm::vec3(0.0, 0.0, -5.0);
        plane.material.ambient = glm::vec3(1, 0.5, 0);
        plane.material.diffuse = glm::vec3(0.0, 1.0, 0.0);
        plane.material.specular =glm::vec3(1.0, 1.0, 1.0);
        plane.material.shininess = 4.0; 
        plane.material.reflection = 0.5;
        plane.normal = glm::vec3(0.0, 1.0, 0.0);

        for (int i = 0; i < spheres.size(); ++i) {
            glUniform3fv(locations.sphereCenter[i], 1, glm::value_ptr(spheres[i].center));
            glUniform1f(locations.sphereRadius[i], spheres[i].radius);
            glUniform3fv(locations.sphereMaterialAmbient[i], 1, glm::value_ptr(spheres[i].material.ambient));
            glUniform3fv(locations.sphereMaterialDiffuse[i], 1, glm::value_ptr(spheres[i].material.diffuse));
            glUniform3fv(locations.sphereMaterialSpecular[i], 1, glm::value_ptr(spheres[i].material.specular));
            glUniform1f(locations.sphereMaterialShininess[i], spheres[i].material.shininess);
            glUniform1f(locations.sphereMaterialReflection[i], spheres[i].material.reflection);
        }

        glUniform3fv(locations.planePoint, 1, glm::value_ptr(plane.point));   // Точка на плоскости
        glUniform3fv(locations.planeNormal, 1, glm::value_ptr(plane.normal)); // Нормаль плоскости
        glUniform3fv(locations.planeMaterialAmbient, 1, glm::value_ptr(plane.material.ambient));  // ambient color
        glUniform3fv(locations.planeMaterialDiffuse, 1, glm::value_ptr(plane.material.diffuse));  // diffuse color
        glUniform1f(locations.planeMaterialShininess, plane.material.shininess);  // shininess
        glUniform1f(locations.planeMaterialReflection, plane.material.reflection);  // reflection
    
        glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
        handleInput(cameraPos);
        glUniform3fv(locations.cameraPos, 1, glm::value_ptr(cameraPos));
        glUniform3fv(locations.lightPos, 1, glm::value_ptr(lightPos));
        glUniform3fv(locations.lightColor, 1, glm::value_ptr(lightColor));
        glUniform1i(locations.spheresCount, spheres.size());
        
        GLuint workGroupSizeX = 32;
        GLuint workGroupSizeY = 32;

        GLuint globalSizeX = (WIDTH + workGroupSizeX - 1) / workGroupSizeX * workGroupSizeX;
        GLuint globalSizeY = (HEIGHT + workGroupSizeY - 1) / workGroupSizeY * workGroupSizeY;

        glDispatchCompute(globalSizeX, globalSizeY, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(quadProgram);
        glBindTexture(GL_TEXTURE_2D, tex_output);
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        window.display();
    }

    return 0;
}
