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
	length++;
	SnakeNode *index;
	index = tail;
	tail = new SnakeNode(scene, model, glm::vec3(tail->position.x+2.0, tail->position.y, tail->position.z), size, index, nullptr);
	index->next = tail;
}

void Snake::Decrease()
{
	length--;
	if (tail->prev != nullptr)
	{
		SnakeNode *index;
		index = tail->prev;
		delete tail;
		tail = index;
	}
	else; // todo À¿Õˆ∑÷÷ß
}

void Snake::Draw()
{
	SnakeNode *index;
	index = head;
	for (int i = 1; i < length; i++)
	{
		index->Draw();
		index = index->next;
	}
	index->Draw();
}

void Snake::InitSnake()
{
	SnakeNode *index;
	head = new SnakeNode(scene, model, position, size, nullptr, nullptr);
	tail = head;
	for (int i = 1; i < length; i++)
	{
		index = tail;
		tail = new SnakeNode(scene, model,glm::vec3(position.x+2.0 * i,position.y,position.z), size,index, nullptr);
		index->next = tail;
	}
}

void Snake::Update()
{
	SnakeNode *index;
	index = tail;
	for (int i = 1; i < length; i++)
	{
		glm::vec3 delta = index->prev->position - index->position;
		index->position += delta * speed;
		index = index->prev;
	}
	head->position = position;
	head->Update();

	for (int i = 1; i < length; i++)
	{
		index = index->next;
		glm::vec3 delta = glm::normalize(index->position - index->prev->position) *2.0f;
		index->position = index->prev->position + delta;
		index->Update();
	}
}
