#include "frame_counter.h"

#include <GLFW/glfw3.h>
#include <iostream>

FrameCounter::FrameCounter() : previousTime(glfwGetTime()){}

int FrameCounter::update(bool print)
{
    double currentTime = glfwGetTime();
    deltaTime = currentTime - previousTime;
    previousTime = currentTime;

    elapsedTime += deltaTime;

    frameCount++;
    if (elapsedTime >= 1.0)
    {
        if (print)
        {
            std::cout << frameCount << "\n";
        }
        fps = frameCount;

        frameCount = 0;
        elapsedTime = 0;
    }
    return fps;
}

int FrameCounter::update()
{
    return update(true);
}
