#pragma once
#include <GLFW/glfw3.h>

class Timer
{
	double lastFrame = 0.0f;

public:
	double deltaTime = 0.0f;

	double Update();
};
