#pragma once
#include "Scene.h"
class GameObject
{
	friend class Scene;
public:
	GameObject() = default;
	GameObject(Scene *scene, Shader *shader, Model *model);
	virtual ~GameObject();
protected:
	glm::vec3 position;
	Scene *scene;	
	Shader *shader;						
	GameObject *parent;
	GameObject *child;
	void Draw();
};

