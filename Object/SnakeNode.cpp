#include "../Head/SnakeNode.h"

SnakeNode::SnakeNode(Scene * scene, Model * model,Tag tag ,glm::vec3 pos, glm::vec3 size,SnakeNode* prev ,SnakeNode* next)
	:GameObject(scene, model,tag,pos, size), prev(prev),next(next)
{
}
SnakeNode::~SnakeNode()
{
}
