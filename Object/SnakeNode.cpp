#include "../Head/SnakeNode.h"

SnakeNode::SnakeNode(Scene * scene, Model * model, glm::vec3 pos, glm::vec3 size,SnakeNode* prev ,SnakeNode* next)
	:GameObject(scene, model, pos, size), prev(prev),next(next)
{
}
SnakeNode::~SnakeNode()
{
}
