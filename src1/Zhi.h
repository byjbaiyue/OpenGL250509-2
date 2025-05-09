#ifndef ZHI_H
#define ZHI_H
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
extern int ckWidth;
extern int ckHeight;


extern unsigned int VAO;
extern unsigned int VBO;

extern std::vector<float> vertices;
extern std::vector<int> indices;
extern glm::vec3 cubePositions[];
extern std::vector<float> triangleVertices;
extern glm::vec3 cpos;
extern glm::vec3 cfront;
extern glm::vec3 cup;
extern GLuint triangleVBO, triangleVAO;
#endif