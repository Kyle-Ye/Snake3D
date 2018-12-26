#include "../Head/Scene.h"
#include "../Head/ResourceManager.h"

Scene::Scene():status(normal)
{
}

void Scene::Update()
{
	ResourceManager::UpdateShadersCamera();
}
void Scene::Render()
{
	for (GameObject* object : ObjectList) {
		object->draw();
	}
}
