#include "../Head/GameObject.h"
GameObject::GameObject()
{

}
GameObject::GameObject(Model &model)
	: model(&model), Position(0,0,0), Size(0.1f), Color(1.0f),Radian(2.0f) ,Rotation(0.0f,0.0f,1.0f),IsSeen(true), Destroyed(false) 
{ 
}

GameObject::GameObject(Model &model, glm::vec3 pos, glm::vec3 size, glm::vec3 color,GLfloat radian, glm::vec3 rotation, GLfloat velocity, GLboolean isSeen, GLboolean destroyed)
	: model(&model), Position(pos), Size(size), Color(color),Radian(radian), Rotation(rotation),IsSeen(isSeen), Destroyed(destroyed) 
{
}

void GameObject::Draw()
{
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::translate(modelMat, Position);
	modelMat = glm::rotate(modelMat, Radian, Rotation);
	model->shader.SetMatrix4("model",modelMat);
	model->Draw();
}