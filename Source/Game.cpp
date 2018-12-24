#include "../Head/Game.h"
#include "../Head/ResourceManager.h"
#include "../Head/SpritRenderer.h"

// Game-related State data
SpriteRenderer  *Renderer;

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
}

void Game::Init()
{
	ResourceManager::LoadShader("shader/sprite.vs", "shader/sprite.fs", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// Load textures
	ResourceManager::LoadTexture("Resource/awesomeface.png", GL_TRUE, "face");
	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
}

void Game::Update(GLfloat dt)
{
	/*glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(ResourceManager::camera.Zoom), (float)this->Width / (float)this->Height, 0.1f, 100.0f);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	glm::mat4 view = ResourceManager::camera.GetViewMatrix();
	ResourceManager::GetShader("sprite").SetMatrix4("view", view);*/
}


void Game::ProcessInput(GLfloat dt)
{

}

void Game::Render()
{
	Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}