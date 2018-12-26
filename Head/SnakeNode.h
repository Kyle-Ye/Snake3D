#pragma once
#include "GameObject.h"
class SnakeNode
	:public GameObject
{
public:
	SnakeNode(Scene * scene, Model * model, glm::vec3 pos, glm::vec3 size, SnakeNode* prev,SnakeNode* next);
	~SnakeNode();
	SnakeNode* prev;
	SnakeNode* next;
};

