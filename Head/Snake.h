#pragma once
#include "GameObject.h"
#include "SnakeNode.h"
#include "Camera.h"

class Snake :
	public GameObject
{
public:
	Snake(Scene *scene, Model *model, glm::vec3 pos, glm::vec3 size,int length);
	~Snake();

	int GetLength();
	void Incress();
	void Decrease();

	void draw() override;
private:
	void InitSnake();
	void Update();

private:
	Scene* scene;           // to use in InitSnake()
	Camera* camera;			//Camera will follow snake head
	SnakeNode* head;
	SnakeNode* tail;
	int length;
	float speed = 10.0f;			//Move speed of the snake
	float sensitivity = 70.0f;		//The speed of changing view

	const float spacing = 2.0f;
	const glm::vec3 headColor = glm::vec3(1, 0, 0);
	const glm::vec3 bodyColor = glm::vec3(0, 1, 1);
};