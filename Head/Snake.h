#pragma once
#include "GameObject.h"
#include "SnakeNode.h"

class Snake :
	public GameObject
{
public:
	Snake(Scene *scene, Model *model, glm::vec3 pos, glm::vec3 size,int length);
	~Snake();

	int GetLength();
	void Incress();
	void Decrease();

	void Draw() override;
private:
	void InitSnake();
	void Update() override;

private:
	Scene* scene;           // to use in InitSnake()
	SnakeNode* head;
	SnakeNode* tail;
	int length;
	float speed = 0.3f;			//Move speed of the snake

	const float spacing = 2.0f;
	const glm::vec3 headColor = glm::vec3(1, 0, 0);
	const glm::vec3 bodyColor = glm::vec3(0, 1, 1);
};