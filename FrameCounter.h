#pragma once

#include <string>

struct FrameCounter
{
    int fps;
    FrameCounter();

    int update();
    int update(bool print);

    private:
        int frameCount;
	    double previousTime;
};
