#include "../Head/Scene.h"
#include "../Head/ResourceManager.h"
#include "../Head/Snake.h"

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
	for (GameObject* object : ObjectList)
	{
		if (glm::distance(snake->position, object->position) < 3)
		{
			switch (object->tag)
			{
			case HEAD:
				break;
			case BODY:
			case DEAD:
				snake->Death();
			case FOOD:
				snake->Incress();
			case WEED:
				snake->Decrease();
			case MINE:
				if(snake->length <= 2)
					snake->Death();
				else 
				for (int i = snake->length/2; i > 0; i--)
				{
					snake->Decrease();
				}
			default:
				break;
			}
		}
	}
}
void Scene::Render()
{
	skybox->Draw();
	for (GameObject* object : ObjectList) {
		object->Draw();
	}
}
