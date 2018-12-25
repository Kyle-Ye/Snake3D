#include "../Head/GameObject.h"
GameObject::GameObject()
{

}
GameObject::GameObject(Model &model)
	: model(&model), Position(0,0,0), Size(0.1f),IsSeen(true), Destroyed(false) 
{ 
}

GameObject::GameObject(Model &model, glm::vec3 pos, glm::vec3 size,GLboolean isSeen, GLboolean destroyed)
	: model(&model), Position(pos), Size(size),IsSeen(isSeen), Destroyed(destroyed) 
{
}

void GameObject::Draw()
{
	glm::mat4 modelMat = glm::mat4(1.0f);

	modelMat = glm::translate(modelMat, Position);
	modelMat = glm::scale(modelMat, Size);
	model->shader.SetMatrix4("model",modelMat);
	model->Draw();
}