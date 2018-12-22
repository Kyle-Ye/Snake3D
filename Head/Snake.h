#pragma once
#include "Camera.h"
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

