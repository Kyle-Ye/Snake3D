#pragma once
#include "GameObject.h"
#include "SnakeNode.h"
#include "Scene.h"

class Snake :
	public GameObject
{
public:
	Snake(Scene *scene, Model *model, Tag tag,glm::vec3 pos, glm::vec3 size,int length);
	~Snake();

	int length;
	void Incress();
	void Decrease();

	void Draw() override;
	void Death();
private:
	void InitSnake();
	void Update() override;

private:
	Scene* scene;           // to use in InitSnake()
	SnakeNode* head;
	SnakeNode* tail;
	
	float speed = 0.3f;			//Move speed of the snake

	const float spacing = 2.0f;
	const glm::vec3 headColor = glm::vec3(1, 0, 0);
	const glm::vec3 bodyColor = glm::vec3(0, 1, 1);
};