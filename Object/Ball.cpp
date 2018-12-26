#include "../Head/Ball.h"

Ball::Ball(): color(1.0f)
{
}
Ball::Ball(Model &model,glm::vec4 color):GameObject(model),color(color)
{

}

void Ball::SetColor(glm::vec4 color)
{
	this->color = color;
}

Ball::~Ball()
{
}
