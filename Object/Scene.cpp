#include "../Head/Scene.h"

Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::FrameCycle()
{
	this->Render();
}

void Scene::Render()
{
	for (GameObject* object : ObjectList) {
		object->Draw();
	}
}

void Scene::RemoveObject(GameObject * gameObject)
{
	for (GameObject *object : ObjectList) {
		if (object == gameObject) {
			ObjectList.remove(object);
			break;
		}
	}
}
