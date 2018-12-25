#include "../Head/MainWindow.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Head/Game.h"
#include "../Head/ResourceManager.h"
#include "../Head/Camera.h"

const unsigned int SCR_WIDTH = 960;//1920
const unsigned int SCR_HEIGHT = 540;//1080

Game SnakeGame(SCR_WIDTH, SCR_HEIGHT);

// Camera
Camera ResourceManager::camera = (glm::vec3(0.0f, 0.0f, 3.0f));
int cursor_flag = 1;
bool firstMode = true;
float lastX = (float)SCR_WIDTH / 2.0f;
float lastY = (float)SCR_HEIGHT / 2.0f;

float visibility_value = 0.2f;

// timing
float deltaTime = 0.0f;// time between current frame and last frame
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_enter_callback(GLFWwindow* window, int entered);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

MainWindow::MainWindow()
{
	success = WindowInit(SCR_WIDTH, SCR_HEIGHT, "Snake");
}
MainWindow::MainWindow(const int width, const int height, const std::string title)
{
	this->success = WindowInit(width, height, title);
}
bool MainWindow::WindowInit(const int width, const int height, const std::string title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode * mode = glfwGetVideoMode(monitor);
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorEnterCallback(window, cursor_enter_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}
void MainWindow::MainLoop()
{
	SnakeGame.State = GAME_START;
	SnakeGame.ViewInit();
	while (SnakeGame.State == GAME_START)
	{
		processInput(window);
		if (glfwWindowShouldClose(window))
			break;

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SnakeGame.ViewUpdate();
		SnakeGame.ViewRender();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	SnakeGame.Init();
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		SnakeGame.Update();
		SnakeGame.Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	ResourceManager::Clear();
	return;
}
MainWindow::~MainWindow()
{
	glfwTerminate();
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void cursor_enter_callback(GLFWwindow * window, int entered)
{
	/* Bug:
	** Once you enter or quit GLFW_CURSOR_DISABLED
	** your xpos and ypos will get wrong
	*/
	if (entered)
	{
		// The cursor entered the client area of the window
	}
	else
	{
		// The cursor left the client area of the window
	}
}
void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	/* Bug:
	** the L and the R will go wrong if you turn around
	** I think maybe I should improve my up mat4 later.
	*/
	if (firstMode)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMode = false;
	}
	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos;
	lastX = (float)xpos;
	lastY = (float)ypos;

	ResourceManager::camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	ResourceManager::camera.ProcessMouseScroll(yoffset);
}
void processInput(GLFWwindow *window)
{
	//注意速度问题 乘以deltaTime
	//demo：
	//	if (this->State == GAME_ACTIVE)
	//	{
	//		GLfloat velocity = PLAYER_VELOCITY * dt;
	//		// Move playerboard
	//		if (this->Keys[GLFW_KEY_A])
	//		{
	//			if (Player->Position.x >= 0)
	//				Player->Position.x -= velocity;
	//		}
	//		if (this->Keys[GLFW_KEY_D])
	//		{
	//			if (Player->Position.x <= this->Width - Player->Size.x)
	//				Player->Position.x += velocity;
	//		}
	//	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (SnakeGame.State == GAME_START)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			switch (SnakeGame.BeginFlag)
			{
			case 1:
				SnakeGame.State = GAME_ACTIVE;
				ResourceManager::Clear();
				break;
			case 2:
				//游戏说明
				break;
			case 3:
				glfwSetWindowShouldClose(window, true);
				break;
			default:
				break;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			if (SnakeGame.BeginFlag < SnakeGame.BeginItemNumber)
				SnakeGame.BeginFlag++;
			else SnakeGame.BeginFlag = 1;
			Sleep(100);
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			if (SnakeGame.BeginFlag >= 1)
				SnakeGame.BeginFlag--;
			else SnakeGame.BeginFlag = SnakeGame.BeginItemNumber;
			Sleep(100);
		}
	}
	if (SnakeGame.State == GAME_ACTIVE)
	{
		float cameraSpeed = 2.5f * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			ResourceManager::camera.ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			ResourceManager::camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			ResourceManager::camera.ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			ResourceManager::camera.ProcessKeyboard(RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS)
	{
		cursor_flag *= -1;
		Sleep(200);
		if (cursor_flag == -1)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		if (cursor_flag == 1)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		glPolygonMode(GL_FRONT, GL_LINE);

}