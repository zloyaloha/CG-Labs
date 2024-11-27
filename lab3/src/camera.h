#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

class Camera {
public:
    Camera(float radius, float height, float angle);
    void update();
    void rotate(float deltaAngle);
    void changeHeight(float deltaHeight);
    void changeRadius(float deltaRadius);

private:
    float _radius; // Радиус траектории камеры
    float _height; // Высота камеры
    float _angle;  // Угол вращения камеры
};