#include "Camera.h"
#include <iostream>

Camera::Camera() : dian(false), Xlast(0), Ylast(0), yaw(-90), pitch(0) {}

Camera::~Camera() {}

void Camera::mouseMove(GLFWwindow* window, double Xpos, double Ypos) {
    double Xweiyi = Xpos - Xlast;
    double Yweiyi = Ylast - Ypos;


    if (dian) {

        std::printf("x=%f,y=%f\n", Xweiyi, Yweiyi);

        yaw += Xweiyi / 2;
        pitch += Yweiyi / 2;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        if (yaw == 360)
            yaw = 0;

        cfront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        cfront.y = sin(glm::radians(pitch));
        cfront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        cfront = glm::normalize(cfront);
    }
    Xlast = Xpos;
    Ylast = Ypos;
}

void Camera::mouseClick(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            std::printf("Left mouse 点击\n");
            dian = true;
        }
        else if (action == GLFW_RELEASE) {
            std::printf("Left mouse 松开\n");
            dian = false;
        }
    }
}

//摄像机移动 写在key里的,如果是其他地方使用请自行完善
//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//{
//    cpos += cfront * cspeed;
//}
//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//{
//    cpos -= cfront * cspeed;
//}
//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//{
//    cpos -= glm::normalize(glm::cross(cfront, cup)) * cspeed;
//}
//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//{
//    cpos += glm::normalize(glm::cross(cfront, cup)) * cspeed;
//}
//if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//{
//    cpos -= glm::vec3(0, 1, 0) * cspeed;
//}
//if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//{
//    cpos += glm::vec3(0, 1, 0) * cspeed;
//}