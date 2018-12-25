#include "../Head/Game.h"
#include "../Head/ResourceManager.h"
#include "../Head/SpriteRenderer.h"
#include "../Head/GameObject.h"

// Game-related State data
SpriteRenderer  *Renderer;
GameObject      *Player;


Game::Game(GLuint width, GLuint height)
	: State(GAME_START), Keys(), Width(width), Height(height), BeginFlag(1)
{

}

Game::~Game()
{
	delete Renderer;
	delete Player;
}

void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.fs", nullptr, "sprite");
	ResourceManager::LoadShader("shaders/naosuit_withoutlight.vs", "shaders/naosuit_withoutlight.fs", nullptr, "nausuit");

	// camera
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	// Load textures
	ResourceManager::LoadTexture("textures/begin_view.jpg", GL_FALSE, "begin_view");
	

	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	// Load levels
	GameLevel one; one.Load("levels/one.lvl", this->Width, this->Height * 0.5);
	GameLevel two; two.Load("levels/two.lvl", this->Width, this->Height * 0.5);
	GameLevel three; three.Load("levels/three.lvl", this->Width, this->Height * 0.5);
	GameLevel four; four.Load("levels/four.lvl", this->Width, this->Height * 0.5);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;
	// Configure game objects
	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
}

void Game::Update(GLfloat dt)
{

}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		// Draw background
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		// Draw level
		this->Levels[this->Level].Draw(*Renderer);
		// Draw player
		Player->Draw(*Renderer);
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
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	
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
		Renderer->DrawSprite(ResourceManager::GetTexture("begin_item"), glm::vec2(360, 70 + 90 * this->BeginFlag), glm::vec2(200,100), 0.0f);
		Renderer->DrawSprite(ResourceManager::GetTexture("select_item"), glm::vec2(200, 100+ 90 * this->BeginFlag), glm::vec2(100, 35), glm::radians(90.0f));
	}
}
