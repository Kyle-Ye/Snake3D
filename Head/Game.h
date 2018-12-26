#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Scene.h"
#include "GameLevel.h"
enum GameState {
	GAME_START,
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};


// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
	// 游戏全局状态
	GameState              State;
	GLuint                 Width, Height;
	// 初始界面相关变量
	int 				   BeginFlag;
	const int              BeginItemNumber = 3;
	
	// 游戏关卡
	//std::vector<GameLevel> Levels;
	//GLuint                 Level;

	Scene *scene;

	// 构造器
	Game(GLuint width, GLuint height);
	~Game();
	
	void ViewInit();
	// GameLoop
	void ViewUpdate();
	void ViewRender();
	
	// Initialize game state (load all shaders/textures/levels)
	void Init();
	// GameLoop
	void Update();
	void Render();

	
};
