#pragma once
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include <List>

class GameObject;

class Scene
{
	friend GameObject;
public:
	Scene();
	~Scene();
	void FrameCycle();
private:
	//Frame cycle
	void Enable();
	void Update();
	void Render();

	void RemoveObject(GameObject *gameObject);

private:
	std::list<GameObject *> ObjectList;
	Camera *camera;
};

