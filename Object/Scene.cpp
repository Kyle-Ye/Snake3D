#include "../Head/Scene.h"



Scene::Scene():status(normal)
{
}


Scene::~Scene()
{
}
void Scene::Render()
{
	for (GameObject* object : ObjectList) {
		object->draw();
	}
}
}
