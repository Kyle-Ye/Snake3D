#pragma once
#include "Camera.h"
enum DIRECATION = {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};
class Snake
{
public:
	Snake();
	~Snake();
	void draw();
	
private:
	int size;
	Camera mCamera;
    void move();
};

