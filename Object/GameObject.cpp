#include "../Head/GameObject.h"

GameObject::GameObject(Scene *scene,Shader *shader,Model *model)
{
	this->scene = scene;
	this->shader = shader;
	this->model = model;
	this->scene->ObjectList.push_back(this);
}
GameObject::GameObject(Scene *scene, Shader *shader, float *vertices,int size)
{
	this->scene = scene;
	this->shader = shader;
	this->vertices =vertices;
	this->size = size;
	this->scene->ObjectList.push_back(this);
}

GameObject::~GameObject()
{
}
