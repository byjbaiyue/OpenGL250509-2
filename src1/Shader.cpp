#include "Shader.h"



std::string loadShaderFromFile(const std::string& filePath);



Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // ���ض����Ƭ����ɫ������
    std::string vertexCode = loadShaderFromFile(vertexPath);
    std::string fragmentCode = loadShaderFromFile(fragmentPath);
   
    // ���ַ���ת��ΪC����ַ���
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    // 2. ������ɫ��
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // ������ɫ��
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // ��ӡ�����������еĻ���
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "������ɫ�������㣺����ʧ��\n" << infoLog << std::endl;
    };
    // Ƭ����ɫ��
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // ��ӡ�����������еĻ���
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "������ɫ����Ƭ�Σ�����ʧ��\n" << infoLog << std::endl;
    };

    // ��ɫ������
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // ��ӡ���Ӵ�������еĻ���
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "������ɫ��������ʧ��\n" << infoLog << std::endl;
    }

    // ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(ID);
}



std::string loadShaderFromFile(const std::string& filePath) {
    std::ifstream shaderFile;
    std::stringstream shaderStream;

    // �����ļ����쳣����
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // ���ļ�
        shaderFile.open(filePath);
        // ���ļ����ݶ����ַ�����
        shaderStream << shaderFile.rdbuf();
        // �ر��ļ�
        shaderFile.close();
    }
    catch (std::ifstream::failure e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << filePath << std::endl;
        return "";
    }

    // ���ַ�����ת��Ϊ�ַ���
    return shaderStream.str();
}