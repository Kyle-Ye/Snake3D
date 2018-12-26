#include "../Head/Timer.h"

Timer::Timer(double lastFrame, double velocity)
	:LastFrame(lastFrame),Velocity(velocity)
{
	
}
Timer::~Timer()
{
}
void Timer::Update()
{
	CurrentFrame = glfwGetTime();
	DeltaTime = CurrentFrame - LastFrame;
	LastFrame = CurrentFrame;
}