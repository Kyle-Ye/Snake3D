#pragma once
#include <GLFW/glfw3.h>
class Timer
{
public:
	double LastFrame;
	double CurrentFrame;
	double DeltaTime;
	double Velocity;
	Timer(double lastFrame = 0.0f,double velocity = 1.0f);
	~Timer();
	void Update();
};

