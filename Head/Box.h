#pragma once
#include "GameObject.h"
class Box :
	public GameObject
{
public:
	Box(Scene *scene, Shader *shader, float *vectices, int size);
	virtual ~Box() re;
private:
	float *vertices;
	int size;
};

