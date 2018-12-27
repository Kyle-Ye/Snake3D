#include "../Head/Scene.h"
#include "../Head/ResourceManager.h"
#include "../Head/Snake.h"
#include "../Head/Camera.h"
#include "../Head/Random.h"

extern Camera camera;

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
	skybox->Draw(camera.GetViewMatrix(), glm::perspective(glm::radians(camera.Zoom), 16.0f / 9.0f, 0.1f, 100.0f));
	
	// Åö×²¼ì²â
	for (GameObject* object : ObjectList)
	{
		if (object->tag == SNAKE|| object->tag == HEAD || object->tag == BODY)
			continue;
		float distance= glm::distance(snake->position, object->position);
		std::cout << distance << std::endl;
		if (distance < 5.0f)
		{
			switch (object->tag)
			{
			//case BODY:
			case DEAD:
				snake->Death();
				break;
			case FOOD:
				snake->Incress();
				object->position = glm::vec3(Random::Range(-50.0f,50.0f), Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f));
				this->Score += 20;
				break;
			case WEED:
				snake->Decrease();
				object->position = glm::vec3(Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f));
				this->Score -= 10;
				break;
			case MINE:
				if(snake->length <= 2)
					snake->Death();
				else 
				for (int i = snake->length/2; i > 0; i--)
				{
					snake->Decrease();
				}
				object->position = glm::vec3(Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f));
				this->Score -= 10;
				break;
			default:
				break;
			}
		}
	}
}
void Scene::Render()
{
	for (GameObject* object : ObjectList) {
		object->Draw();
	}
}
