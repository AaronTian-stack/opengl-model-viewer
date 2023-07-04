#include "FrameCounter.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

FrameCounter::FrameCounter()
{
	previousTime = glfwGetTime();
	frameCount = 0;
}

void FrameCounter::update()
{
	double currentTime = glfwGetTime();
	frameCount++;
	if (currentTime - previousTime >= 1.0)
	{
		std::cout << frameCount << "\n";

		frameCount = 0;
		previousTime = currentTime;
	}
}
