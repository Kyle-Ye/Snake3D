#pragma once
#include <List>
#include "GameObject.h"
#include "SkyBox.h"

enum GameStatus {
	normal,
	pause,
	death,
	win
};
class Snake;
class Scene
{
public:
	int	Score = 0;
	Scene();
	~Scene();
	Skybox *skybox;
	Snake *snake;
	std::list<GameObject*> ObjectList;
	GameStatus status;
	void Update();
	void Render();
};

