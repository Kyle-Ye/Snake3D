#pragma once
#include <List>
#include "GameObject.h"
enum GameStatus {
	normal,
	pause
};

class Scene
{
public:
	Scene();
	~Scene();
	std::list<GameObject*> ObjectList;
	GameStatus status;
	void Render();
};

