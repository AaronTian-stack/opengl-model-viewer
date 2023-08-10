#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Window
{
	GLFWwindow* window;
	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;

	Window(int SCR_WIDTH, int SCR_HEIGHT,
           GLFWframebuffersizefun framebuffer_size_callback,
           GLFWcursorposfun mouse_callback,
           GLFWscrollfun scroll_callback,
           GLFWkeyfun toggleCursor
           );

    float getAspectRatio() const;
};
