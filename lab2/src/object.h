#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <vector>
#include <glm/glm.hpp>

struct Light {
    glm::vec3 position;
    glm::vec3 color;
};

class Object3D {
public:
    Object3D(float size);
    void draw();
    void rotateCube(float angleX, float angleY, float angleZ);
    void addLight(const Light& light);
    // glm::vec3 calculateNormal(Vertex3D& v1, Vertex3D& v2, Vertex3D& v3);
private:
    float _size;
    std::vector<Light> lights;
    float _angleX, _angleY, _angleZ;
};

#endif // OBJECT3D_H
