#include "Window.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window(int SCR_WIDTH, int SCR_HEIGHT, GLFWframebuffersizefun framebuffer_size_callback)
{
	this->SCR_WIDTH = SCR_HEIGHT;
	this->SCR_HEIGHT = SCR_HEIGHT;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window \n";
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD \n";
	}

	// v sync
	glfwSwapInterval(1); 
}
