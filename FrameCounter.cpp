#include "FrameCounter.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

FrameCounter::FrameCounter()
{
	previousTime = glfwGetTime();
	frameCount = 0;
}

void FrameCounter::update(bool print) {
    double currentTime = glfwGetTime();
    frameCount++;
    if (currentTime - previousTime >= 1.0)
    {
        if (print)
            std::cout << frameCount << "\n";

        frameCount = 0;
        previousTime = currentTime;
    }
}

void FrameCounter::update() {
    update(true);
}
