#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "GameLevel.h"
enum GameState {
	GAME_START,
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100, 20);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(500.0f);

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
	// ��Ϸȫ��״̬
	GameState              State;
	GLuint                 Width, Height;
	// ��ʼ������ر���
	int 				   BeginFlag;
	const int              BeginItemNumber = 3;
	
	// ��Ϸ�ؿ�
	std::vector<GameLevel> Levels;
	GLuint                 Level;

	// ������
	Game(GLuint width, GLuint height);
	~Game();

	// Initialize game state (load all shaders/textures/levels)
	void Init();
	// GameLoop
	void Update();
	void Render();

	void ViewInit();
	void ViewUpdate();
	void ViewRender();
};
