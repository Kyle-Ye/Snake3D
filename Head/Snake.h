#pragma once
#include "Camera.h"
class Snake :
	public GameObject
{
public:
	Snake();
	~Snake();

	int GetLength();
	void Incress();
	void Decress();

	void ActivateCamera();
	const SnakeNode* GetHead();

	void OnEatFood();

private:
	void InitSnake();
	void ChangeHead(SnakeNode* newHead);
	void Update();

private:
	Camera* camera;			//Camera will follow snake head
	GameObject* head;
	GameObject* tail;
	int length;
	float speed = 10.0f;			//Move speed of the snake
	float sensitivity = 70.0f;		//The speed of changing view

	const float spacing = 2.0f;
	const glm::vec3 headColor = glm::vec3(1, 0, 0);
	const glm::vec3 bodyColor = glm::vec3(0, 1, 1);

