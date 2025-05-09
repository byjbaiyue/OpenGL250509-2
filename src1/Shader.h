#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


#define GLEW_STATIC
#include <gl/glew.h> // ����glew����ȡ���еı���OpenGLͷ�ļ�
#include <GLFW/glfw3.h>

class Shader
{
public:
    // ����ID
    unsigned int ID;

    // ��������ȡ��������ɫ��
    Shader(const char* vertexPath, const char* fragmentPath);

    // ʹ��/�������
    void use();
    // uniform���ߺ���
    //void setBool(const std::string& name, bool value) const;
    //void setInt(const std::string& name, int value) const;
    //void setFloat(const std::string& name, float value) const;
};

#endif