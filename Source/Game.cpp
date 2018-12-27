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
	: State(GAME_START), Width(width), Height(height), BeginFlag(1)
{

}

Game::~Game()
{
	delete Renderer;
}

void Game::Init(Scene *scene)
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
	ResourceManager::LoadModel("models/ball/Ball.obj","ball",ResourceManager::GetShader("ball"));
	ResourceManager::LoadModel("models/ball/Ball.obj", "food", ResourceManager::GetShader("food"));
	ResourceManager::LoadModel("models/ball/Ball.obj", "weed", ResourceManager::GetShader("weed"));
	ResourceManager::LoadModel("models/ball/Ball.obj", "mine", ResourceManager::GetShader("mine"));
	ResourceManager::LoadModel("models/ball/Ball.obj", "snake", ResourceManager::GetShader("snake"));

	// Load Textures

	// Set Objects
	for (int i = 0; i < 40; i++)
	{
		new GameObject(this->scene, &ResourceManager::GetModel("food"), FOOD, glm::vec3(Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f)), glm::vec3(0.15f));
		new Weed(this->scene, &ResourceManager::GetModel("weed"), WEED, glm::vec3(Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f)), glm::vec3(0.2f));
	}
	for (int i = 0; i < 30; i++)
	{
		new GameObject(this->scene, &ResourceManager::GetModel("mine"), MINE, glm::vec3(Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f), Random::Range(-50.0f, 50.0f)), glm::vec3(0.15f));
	}

	snake = new Snake(this->scene, &ResourceManager::GetModel("snake"),SNAKE,camera.getPosition(), glm::vec3(1.0f),5);

	this->scene->snake = snake;
	// Bind camera
	camera.Bind(snake);

	this->scene->skybox = new Skybox ("skybox");
	// Load levelss
	/*GameLevel one; one.Load("levels/one.lvl", this->Width, this->Height * 0.5);
	GameLevel two; two.Load("levels/two.lvl", this->Width, this->Height * 0.5);
	GameLevel three; three.Load("levels/three.lvl", this->Width, this->Height * 0.5);
	GameLevel four; four.Load("levels/four.lvl", this->Width, this->Height * 0.5);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;*/
	// Configure game objects
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
		this->State = GAME_LOSE;
		break;
	case win:
		
	default:
		break;
	}
}

void Game::ViewInit()
{
	// Load shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.fs", nullptr, "sprite");
	
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	// Load textures
	ResourceManager::LoadTexture("textures/begin_view.jpg", GL_FALSE, "begin_view");
	ResourceManager::LoadTexture("textures/paddle.png", GL_TRUE, "select_item");

	// Set render-specific controls
	Renderer = new SpriteRenderer2D(ResourceManager::GetShader("sprite"));
	
}

void Game::ViewUpdate()
{
	switch (this->BeginFlag)
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

void Game::ViewRender()
{
	if (this->State == GAME_START)
	{
		Renderer->DrawSprite(ResourceManager::GetTexture("begin_view"),glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		Renderer->DrawSprite(ResourceManager::GetTexture("select_item"), glm::vec2(200, 100 + 90 * this->BeginFlag), glm::vec2(100, 35), glm::radians(90.0f));
		Renderer->DrawSprite(ResourceManager::GetTexture("begin_item"), glm::vec2(360, 70 + 90 * this->BeginFlag), glm::vec2(200, 100), 0.0f);
	
	
	}
}
