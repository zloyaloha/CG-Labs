#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

struct Light {
    glm::vec3 position;
    glm::vec3 dir;
    glm::vec3 color;
};

class Cube {
public:
    Cube(float size);
    void draw(const glm::mat4& view, const glm::mat4& projection, const Light& light);
    void setShaderProgram(GLuint shaderProgram);

private:
    Light lights;
    GLuint VAO, VBO;
    GLuint shaderProgram;
    float size;
    glm::vec3 vertices[8]; 
    glm::vec3 cubeVertices[36];
    glm::vec3 objColor;
    void setupCube();

    void setUniforms(const glm::mat4& view, const glm::mat4& projection, const Light& light, int type);
};