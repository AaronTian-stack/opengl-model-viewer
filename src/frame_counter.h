#pragma once

struct FrameCounter
{
    int fps;
    double deltaTime;
    FrameCounter();

    int update();
    int update(bool print);

    private:
        int frameCount;
	    double previousTime;
        double elapsedTime;
};
