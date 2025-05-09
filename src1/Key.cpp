#include "Key.h"
#include "Zhi.h"

void Key(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		printf("ESC�˳�");
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		// �޸�  �����е�ֵ
		vertices[2] += 0.1f;
		// ���޸ĺ�����������ϴ��� VBO ��
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		// �޸�  �����е�ֵ
		vertices[2] -= 0.1f;
		// ���޸ĺ�����������ϴ��� VBO ��
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
	}



	//������ٶ�
	float cspeed = 0.1;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		cspeed = 0.8;
	}
	else { cspeed = 0.1; }

	//������ƶ�
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cpos += cfront * cspeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cpos -= cfront * cspeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cpos -= glm::normalize(glm::cross(cfront, cup)) * cspeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cpos += glm::normalize(glm::cross(cfront, cup)) * cspeed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		cpos -= glm::vec3(0, 1, 0) * cspeed;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		cpos += glm::vec3(0, 1, 0) * cspeed;
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		cpos = glm::vec3(0, -2, 0);
	}
}

