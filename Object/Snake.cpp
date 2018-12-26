#include "../Head/Snake.h"

Snake::Snake(Scene * scene, Model * model, glm::vec3 pos, glm::vec3 size, int length)
	:GameObject(scene, model, pos, size),length(length),scene(scene)
{
	InitSnake();
}

Snake::~Snake()
{
}

int Snake::GetLength()
{
	return length;
}

void Snake::Incress()
{
}

void Snake::Decress()
{
}

void Snake::OnEatFood()
{
}

void Snake::draw()
{
	SnakeNode *index;
	index = head;
	for (int i = 0; i < length - 1; i++)
	{
		index->draw();
		index = index->next;
	}
	index->draw();
}

void Snake::InitSnake()
{
	SnakeNode *index;
	head = new SnakeNode(scene, model, position, size, nullptr, nullptr);
	tail = head;
	for (int i = 1; i < length; i++)
	{
		index = tail;
		tail = new SnakeNode(scene, model,glm::vec3(position.x,position.y+1.0*i,position.z), size,index, nullptr);
		index->next = tail;
	}
}

void Snake::Update()
{
}
