#include "../Head/Scene.h"
#include "../Head/ResourceManager.h"

Scene::Scene():status(normal)
{
}

Scene::~Scene()
{
	delete skybox;
}

void Scene::Update()
{
	ResourceManager::UpdateShadersCamera();
	for (GameObject* object : ObjectList) {
		object->Update();
	}
	skybox->Draw();
}
void Scene::Render()
{
	
	for (GameObject* object : ObjectList) {
		object->Draw();
	}
}
