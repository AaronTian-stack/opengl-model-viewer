#include "FrameCounter.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

FrameCounter::FrameCounter()
{
	previousTime = glfwGetTime();
	frameCount = 0;
}

int FrameCounter::update(bool print)
{
    double currentTime = glfwGetTime();
    frameCount++;
    if (currentTime - previousTime >= 1.0)
    {
        if (print)
        {
            std::cout << frameCount << "\n";
        }
        fps = frameCount;

        frameCount = 0;
        previousTime = currentTime;
    }
    return fps;
}

int FrameCounter::update()
{
    return update(true);
}
