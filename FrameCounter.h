#pragma once

#include <string>

struct FrameCounter
{
	int frameCount;
	FrameCounter();

	void update();
    void update(bool print);

    std::string toString();

private:
	double previousTime;
};
