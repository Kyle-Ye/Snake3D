#include "../Head/GameObject.h"
#include "../Head/Scene.h"

GameObject::GameObject(Scene * scene, Model * model, Tag tag,glm::vec3 pos, glm::vec3 size)
	:model(model),position(pos),size(size),tag(tag)
{
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::translate(modelMat, pos);
	modelMat = glm::scale(modelMat, size);
	this->modelMat = modelMat;
	scene->ObjectList.push_back(this);
}

void GameObject::Draw()
{
	model->shader.SetMatrix4("model",this->modelMat);
	model->Draw();
}

void GameObject::Update()
{
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::translate(modelMat, position);
	modelMat = glm::scale(modelMat, size);
	this->modelMat = modelMat;
}

void GameObject::Update(glm::vec3 position)
{
	this->position = position;
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::translate(modelMat, position);
	this->modelMat = modelMat;
}

void GameObject::Update(glm::vec3 position, glm::vec3 size)
{
	this->position = position;
	this->size = size;
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::translate(modelMat, position);
	modelMat = glm::scale(modelMat, size);
	this->modelMat = modelMat;
	
}
