#include "Scene.h"

Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::FrameCycle()
{
	this->Enable();
	this->Update();
	this->Render();
}

void Scene::Enable()
{
	for (GameObject* object : ObjectList) {
		if (object->isPreActive) {
			object->PreEnable();
			object->OnEnable();
		}
	}
}

void Scene::Update()
{
	for (GameObject* object : ObjectList) {
		object->Update();
	}
}

void Scene::Render()
{
	for (GameObject* object : ObjectList) {
		if (object->isRendereringEnable) {
			object->PreRender();
			object->Render();
			object->PostRender();
		}
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
