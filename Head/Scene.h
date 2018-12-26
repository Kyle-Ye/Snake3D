#pragma once
#include <List>
#include "GameObject.h"
#include "SkyBox.h"

enum GameStatus {
	normal,
	pause
};

class Scene
{
public:
	Scene();
	~Scene();
	Skybox *skybox;
	std::list<GameObject*> ObjectList;
	GameStatus status;
	void Update();
	void Render();
};

