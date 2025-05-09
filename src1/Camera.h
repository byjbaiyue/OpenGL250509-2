#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Zhi.h"
class Camera {
public:
    Camera();
    ~Camera();

    void mouseMove(GLFWwindow* window, double Xpos, double Ypos);
    void mouseClick(GLFWwindow* window, int button, int action, int mods);

private:
    bool dian;
    double Xlast, Ylast;
    double yaw, pitch;
};

#endif // CAMERA_H