


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>


//�Զ���ͷ�ļ�
#include "Zhi.h"
#include "Key.h"
#include "Shader.h"
#include "jzTexCoord.h"
#include "Camera.h"


//�����ĺ�������
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Camera camera;


int main() {

	// ��ʼ�� GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// ���� OpenGL �����İ汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//�������ڶ���
	GLFWwindow* window = glfwCreateWindow(ckWidth, ckHeight, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		printf("���� GLFW ����ʧ��");
		//��ֹ GLFW �����в��ͷ������� GLFW ��ص���Դ
		glfwTerminate();
		return -1;
	}
	//�������õ�ǰ�� OpenGL ������
	glfwMakeContextCurrent(window);

	// ��ʼ�� GLEW
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return -1;
	}


	//������ɫ��
	Shader shader("src1/shader/VertexShader.txt", "src1/shader/FragmentShader.txt");


	

	//��������
	jzTexCoord();

	shader.use();

	glUniform1i(glGetUniformLocation(shader.ID, "ourTexture1"), 0);
	glUniform1i(glGetUniformLocation(shader.ID, "ourTexture2"), 1);
	
	//ģ�;���
	glm::mat4 model = glm::mat4(1.0f);
	//�ӽǾ���
	glm::mat4 view = glm::mat4(1.0f);
	//ͶӰ����
	glm::mat4 projection = glm::mat4(1.0f);
	
	

	//����ƶ� �ص�����
	glfwSetCursorPosCallback(window, [](GLFWwindow* win, double xpos, double ypos) {
		camera.mouseMove(win, xpos, ypos);
		});
	//�����
	glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods) {
		camera.mouseClick(win, button, action, mods);
		});
	//������ÿ�δ��ڴ�С��������ʱ�򱻵���
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSwapInterval(1);
	//Z����
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{


		Key(window);


		//���������Ļ���õ���ɫ
		glClearColor(0.8f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(VAO);
		//��ʱ��ı���ɫ���
		float timeValue = glfwGetTime();
		float deepValue = sin(4 * timeValue) * sin(4 * timeValue);
		glUniform4f(glGetUniformLocation(shader.ID, "ourColor1"), deepValue, deepValue, deepValue, 1.0);

		//���������������
		view = glm::lookAt(cpos, cfront + cpos, glm::vec3(0.0f, 1.0f, 0.0f));

		projection = glm::perspective(glm::radians(45.0f), (float)ckWidth / (float)ckHeight, 0.1f, 1000.0f);


		
		glUniform1i(glGetUniformLocation(shader.ID, "useTexture"), 1);
		for (unsigned int i = 0; i < 16; i++) {
			//ģ��
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(1.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			//���Ʒ���
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		}


		//����������ģ�;���
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0,-3,0));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(shader.ID, "ourColor1"),1,1,1,1);
		glUniform1i(glGetUniformLocation(shader.ID, "useTexture"),0);
		//����������
		glBindVertexArray(triangleVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		if (cpos.y >= -2) {
			cpos.y -= 0.03f;
		}
		if (cpos.y < -2) {
			cpos.y += -2 - cpos.y;
		}



		//���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����
		glfwSwapBuffers(window);
		//�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б���������
		glfwPollEvents();
	}

	//ɾ��������Դ
	glfwTerminate();
	return 0;
}

//
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	if (height == 0) height = 1; // ��ֹ����0
	if (width == 0) width = 1;  // ��ֹ���Ϊ0
	glViewport(0, 0, width, height);
	ckWidth = width;
	ckHeight = height;
}