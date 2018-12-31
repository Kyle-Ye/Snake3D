#include "../Head/Game.h"

#include "../Head/Camera.h"
#include "../Head/Timer.h"
#include "../Head/ResourceManager.h"
#include "../Head/SpriteRenderer2D.h"
#include "../Head/GameObject.h"
#include "../Head/Snake.h"
#include "../Head/SkyBox.h"
#include "../Head/Random.h"
#include "../Head/Weed.h"

// Game-related State data
SpriteRenderer2D  *Renderer;
Snake *snake;
extern Camera camera;
extern Timer gameTime;

Game::Game(GLuint width, GLuint height)
	: Stage(GAME_START), Width(width), Height(height), Flag(1)
{

}

Game::~Game()
{
	delete Renderer;
}

void Game::showUIMenu()
{
	if (!isInitUI)
	{
		InitUI();
		isInitUI = true;
	}
	MenuUpdate();
	MenuRender();
}

void Game::showUIChoose()
{
	ChooseUpdate();
	ChooseRender();
}

void Game::showUIWin()
{
	Renderer->DrawSprite(ResourceManager::GetTexture("win"), glm::vec2(100, 200), glm::vec2(200, 100), 0.0f);
}

void Game::showUILose()
{
	Renderer->DrawSprite(ResourceManager::GetTexture("lose"), glm::vec2(100, 200), glm::vec2(200, 100), 0.0f);
}

void Game::InitUI()
{
	// Load shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.fs", nullptr, "sprite");

	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	// Load textures
	ResourceManager::LoadTexture("textures/title.png", GL_TRUE, "title");
	ResourceManager::LoadTexture("textures/background.jpg", GL_FALSE, "background");
	ResourceManager::LoadTexture("textures/paddle.png", GL_TRUE, "select_item");

	ResourceManager::LoadTexture("textures/background2.jpg", GL_FALSE, "background2");
	ResourceManager::LoadTexture("textures/maptitle.png", GL_TRUE, "maptitle");
	ResourceManager::LoadTexture("textures/difficultytitle.png", GL_TRUE, "difficultytitle");

	ResourceManager::LoadTexture("textures/win.png", GL_TRUE, "win");
	ResourceManager::LoadTexture("textures/lose.png", GL_TRUE, "lose");

	// Set render-specific controls
	Renderer = new SpriteRenderer2D(ResourceManager::GetShader("sprite"));
}

void Game::InitGame(Scene *scene)
{

	this->scene = scene;
	// Load shaders
	ResourceManager::LoadShader("shaders/nanosuit.vs", "shaders/nanosuit.fs", nullptr, "nanosuit");
	ResourceManager::LoadShader("shaders/ball.vs", "shaders/ball.fs", nullptr, "ball");
	ResourceManager::LoadShader("shaders/food.vs", "shaders/food.fs", nullptr, "food");
	ResourceManager::LoadShader("shaders/weed.vs", "shaders/weed.fs", nullptr, "weed");
	ResourceManager::LoadShader("shaders/mine.vs", "shaders/mine.fs", nullptr, "mine");
	ResourceManager::LoadShader("shaders/snake.vs", "shaders/snake.fs", nullptr, "snake");

	// Load Models
	ResourceManager::LoadModel("models/nanosuit/nanosuit.obj", "nanosuit", ResourceManager::GetShader("nanosuit"));
	ResourceManager::LoadModel("models/ball/Ball.obj", "ball", ResourceManager::GetShader("ball"));
	ResourceManager::LoadModel("models/ball/Ball.obj", "food", ResourceManager::GetShader("food"));
	ResourceManager::LoadModel("models/ball/Ball.obj", "weed", ResourceManager::GetShader("weed"));
	ResourceManager::LoadModel("models/ball/Ball.obj", "mine", ResourceManager::GetShader("mine"));
	ResourceManager::LoadModel("models/ball/Ball.obj", "snake", ResourceManager::GetShader("snake"));

	// Load Textures

	// Set Objects
	int NF, NM;
	switch (Difficulty)
	{
	case 1:
		NF = 40;
		NM = 10;
		break;
	case 2:
		NF = 25;
		NM = 25;
		break;
	case 3:
		NF = 20;
		NM = 30;
		break;
	}
	for (int i = 0; i < NF; i++)
	{
		new GameObject(this->scene, &ResourceManager::GetModel("food"), FOOD, glm::vec3(Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f)), glm::vec3(0.15f));
		new Weed(this->scene, &ResourceManager::GetModel("weed"), WEED, glm::vec3(Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f)), glm::vec3(0.2f));
	}
	for (int i = 0; i < NM; i++)
	{
		new GameObject(this->scene, &ResourceManager::GetModel("mine"), MINE, glm::vec3(Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f)), glm::vec3(0.15f));
	}

	snake = new Snake(this->scene, &ResourceManager::GetModel("snake"), SNAKE, camera.getPosition(), glm::vec3(1.0f), 5);

	this->scene->snake = snake;
	// Bind camera
	camera.Bind(snake);
	switch (Map)
	{
	case 1:
		this->scene->skybox = new Skybox("skybox/sunshine");
		break;
	case 2:
		this->scene->skybox = new Skybox("skybox/fire");
		break;
	case 3:
		this->scene->skybox = new Skybox("skybox/dessert");
		break;
	default:
		break;
	}
}

void Game::FrameCycle()
{
	switch (scene->status)
	{
	case normal:
		camera.ProcessKeyboard(FORWARD, gameTime.DeltaTime);
		this->scene->Update();
		this->scene->Render();
		break;
	case pause:
		break;
	case death:
		this->Stage = GAME_LOSE;
		this->Flag = 5;
		break;
	case win:
		this->Stage = GAME_WIN;
		this->Flag = 4;

		break;
	default:
		break;
	}
}


void Game::MenuUpdate()
{
	switch (this->Flag)
	{
	case 1:
		ResourceManager::LoadTexture("textures/begin_item1.png", GL_TRUE, "begin_item");
		break;
	case 2:
		ResourceManager::LoadTexture("textures/begin_item2.png", GL_TRUE, "begin_item");
		break;
	case 3:
		ResourceManager::LoadTexture("textures/begin_item3.png", GL_TRUE, "begin_item");
		break;
	default:
		break;
	}
}

void Game::MenuRender()
{
	Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
	Renderer->DrawSprite(ResourceManager::GetTexture("title"), glm::vec2(250, -50), glm::vec2(500, 200), 0.0f);
	Renderer->DrawSprite(ResourceManager::GetTexture("select_item"), glm::vec2(200, 100 + 90 * this->Flag), glm::vec2(100, 35), glm::radians(90.0f));
	Renderer->DrawSprite(ResourceManager::GetTexture("begin_item"), glm::vec2(360, 70 + 90 * this->Flag), glm::vec2(200, 100), 0.0f);
}

void Game::ChooseUpdate()
{
	switch (this->Difficulty)
	{
	case 1:
		ResourceManager::LoadTexture("textures/1.png", GL_TRUE, "difficultynumber");
		break;
	case 2:
		ResourceManager::LoadTexture("textures/2.png", GL_TRUE, "difficultynumber");
		break;
	case 3:
		ResourceManager::LoadTexture("textures/3.png", GL_TRUE, "difficultynumber");
		break;
	default:
		break;
	}
	switch (this->Map)
	{
	case 1:
		ResourceManager::LoadTexture("textures/1.png", GL_TRUE, "mapnumber");
		break;
	case 2:
		ResourceManager::LoadTexture("textures/2.png", GL_TRUE, "mapnumber");
		break;
	case 3:
		ResourceManager::LoadTexture("textures/3.png", GL_TRUE, "mapnumber");
		break;
	default:
		break;
	}
}

void Game::ChooseRender()
{
	Renderer->DrawSprite(ResourceManager::GetTexture("background2"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
	Renderer->DrawSprite(ResourceManager::GetTexture("maptitle"), glm::vec2(250, 50), glm::vec2(100, 100), 0.0f);
	Renderer->DrawSprite(ResourceManager::GetTexture("difficultytitle"), glm::vec2(250, 200), glm::vec2(100, 100), 0.0f);
	Renderer->DrawSprite(ResourceManager::GetTexture("mapnumber"), glm::vec2(270, 50), glm::vec2(100, 100), 0.0f);
	Renderer->DrawSprite(ResourceManager::GetTexture("difficultynumber"), glm::vec2(270, 200), glm::vec2(100, 100), 0.0f);
}
