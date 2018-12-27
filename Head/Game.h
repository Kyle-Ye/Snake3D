#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Scene.h"

enum GameStage {
	GAME_START,
	GAME_CHOOSE,
	GAME_ACTIVE,
	GAME_WIN,
	GAME_LOSE,
	GAME_EXIT
};


// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
	// 游戏全局状态
	GameStage Stage;
	GLuint Width, Height;
	
	// 初始界面相关变量
	int Flag=1;
	int Map = 1;
	int Difficulty = 1;
	const int BeginItemNumber = 3;

	Scene *scene;

	// 构造器
	Game(GLuint width, GLuint height);
	~Game();
	
	void showUIMenu();
	void showUIChoose();
	void showUIWin();
	void showUILose();

	void InitGame(Scene *scene);
	// GameLoop
	void FrameCycle();
private:
	bool isInitUI = false;
	
	void InitUI();
	
	void MenuUpdate();
	void MenuRender();

	void ChooseUpdate();
	void ChooseRender();
};
