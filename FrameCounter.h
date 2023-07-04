#pragma once

struct FrameCounter
{
	int frameCount;
	FrameCounter();
	void update();

private:
	double previousTime;
};
