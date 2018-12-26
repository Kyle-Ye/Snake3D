#include "../Head/GameObject.h"

GameObject::GameObject(Scene * scene, Model * model, glm::vec3 pos, glm::vec3 size)
	:scene(scene), model(model),position(pos),size(size)
{
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::translate(modelMat, pos);
	modelMat = glm::scale(modelMat, size);
	this->modelMat = modelMat;
	scene->ObjectList.push_back(this);
}
void GameObject::draw()
{
	model->shader.SetMatrix4("model",this->modelMat);
	model->Draw();
}

void GameObject::update(glm::vec3 position)
{
	this->position = position;
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::translate(modelMat, position);
	this->modelMat = modelMat;
}

void GameObject::update(glm::vec3 position, glm::vec3 size)
{
	this->position = position;
	this->size = size;
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::translate(modelMat, position);
	modelMat = glm::scale(modelMat, size);
	this->modelMat = modelMat;
	
}
