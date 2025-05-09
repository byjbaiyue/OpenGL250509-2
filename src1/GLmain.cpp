


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>


//自定义头文件
#include "Zhi.h"
#include "Key.h"
#include "Shader.h"
#include "jzTexCoord.h"
#include "Camera.h"


//声明的函数和类
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Camera camera;


int main() {

	// 初始化 GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// 设置 OpenGL 上下文版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//创建窗口对象
	GLFWwindow* window = glfwCreateWindow(ckWidth, ckHeight, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		printf("创建 GLFW 窗口失败");
		//终止 GLFW 的运行并释放所有与 GLFW 相关的资源
		glfwTerminate();
		return -1;
	}
	//用于设置当前的 OpenGL 上下文
	glfwMakeContextCurrent(window);

	// 初始化 GLEW
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return -1;
	}


	//创建着色器
	Shader shader("src1/shader/VertexShader.txt", "src1/shader/FragmentShader.txt");


	

	//加载纹理
	jzTexCoord();

	shader.use();

	glUniform1i(glGetUniformLocation(shader.ID, "ourTexture1"), 0);
	glUniform1i(glGetUniformLocation(shader.ID, "ourTexture2"), 1);
	
	//模型矩阵
	glm::mat4 model = glm::mat4(1.0f);
	//视角矩阵
	glm::mat4 view = glm::mat4(1.0f);
	//投影矩阵
	glm::mat4 projection = glm::mat4(1.0f);
	
	

	//鼠标移动 回调函数
	glfwSetCursorPosCallback(window, [](GLFWwindow* win, double xpos, double ypos) {
		camera.mouseMove(win, xpos, ypos);
		});
	//鼠标点击
	glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods) {
		camera.mouseClick(win, button, action, mods);
		});
	//它会在每次窗口大小被调整的时候被调用
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSwapInterval(1);
	//Z缓冲
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{


		Key(window);


		//设置清空屏幕所用的颜色
		glClearColor(0.8f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(VAO);
		//随时间改变颜色深度
		float timeValue = glfwGetTime();
		float deepValue = sin(4 * timeValue) * sin(4 * timeValue);
		glUniform4f(glGetUniformLocation(shader.ID, "ourColor1"), deepValue, deepValue, deepValue, 1.0);

		//计算摄像机的向量
		view = glm::lookAt(cpos, cfront + cpos, glm::vec3(0.0f, 1.0f, 0.0f));

		projection = glm::perspective(glm::radians(45.0f), (float)ckWidth / (float)ckHeight, 0.1f, 1000.0f);


		
		glUniform1i(glGetUniformLocation(shader.ID, "useTexture"), 1);
		for (unsigned int i = 0; i < 16; i++) {
			//模型
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(1.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			//绘制方块
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		}


		//更新三角形模型矩阵
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0,-3,0));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(shader.ID, "ourColor1"),1,1,1,1);
		glUniform1i(glGetUniformLocation(shader.ID, "useTexture"),0);
		//绘制三角形
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



		//函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数
		glfwSwapBuffers(window);
		//函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制
		glfwPollEvents();
	}

	//删除所有资源
	glfwTerminate();
	return 0;
}

//
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	if (height == 0) height = 1; // 防止除以0
	if (width == 0) width = 1;  // 防止宽度为0
	glViewport(0, 0, width, height);
	ckWidth = width;
	ckHeight = height;
}