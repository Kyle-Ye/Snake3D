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
	else; // todo ËÀÍö·ÖÖ§
}

void Snake::BindCamera(Camera * camera)
{
	this->camera = camera;
}

void Snake::draw()
{
	SnakeNode *index;
	index = head;
	for (int i = 1; i < length; i++)
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
		index->position = index->prev->position;
		index = index->prev;
	}
	head->position = camera->getPosition;
}
