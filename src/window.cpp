#include "window.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window(int SCR_WIDTH, int SCR_HEIGHT,
               GLFWframebuffersizefun framebuffer_size_callback,
               GLFWcursorposfun mouse_callback,
               GLFWscrollfun scroll_callback,
               GLFWkeyfun toggleCursor
               )
{
	this->SCR_WIDTH = SCR_HEIGHT;
	this->SCR_HEIGHT = SCR_HEIGHT;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Model Viewer", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window \n";
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetKeyCallback(window, toggleCursor);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD \n";
	}

    const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString (GL_VERSION); // version as a string
    std::cout<<"Renderer: "<<renderer<<std::endl;
    std::cout<<"OpenGL version supported "<<version<<std::endl;

    // anti aliasing
    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);

    // v sync
	glfwSwapInterval(1);
}

float Window::getAspectRatio() const {
    return float(SCR_WIDTH) / float(SCR_HEIGHT);
}
