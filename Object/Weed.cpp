#include "../Head/Weed.h"
#include "../Head/Timer.h"
#include "../Head/Model.h"
extern Timer gameTime;

Weed::Weed(Scene *scene, Model *model, Tag tag, glm::vec3 pos, glm::vec3 size)
	:GameObject(scene, model, tag, pos, size)
{
}


Weed::~Weed()
{
}
void Weed::Draw()
{
	model->shader.SetMatrix4("model", this->modelMat);
	model->shader.SetVector3f("myColor",abs(sin(gameTime.CurrentFrame+2)), abs(cos(gameTime.CurrentFrame)), abs(sin(gameTime.CurrentFrame)));
	model->Draw();
}