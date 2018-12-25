#include "../Head/Ball.h"

Ball::Ball(): color(1.0f)
{
}
Ball::Ball(glm::vec4 color)
{
	this->color = color;
}

void Ball::SetColor(glm::vec4 color)
{
	this->color = color;
}

Ball::~Ball()
{
}
