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
#include "../Head/Timer.h"

const unsigned int SCR_WIDTH = 960;//1920
const unsigned int SCR_HEIGHT = 540;//1080

glm::vec3 birthplace(0.0f,0.0f,3.0f);

Game SnakeGame(SCR_WIDTH, SCR_HEIGHT);
Camera camera = birthplace;
Timer gameTime(0.0, 1.0);

int cursor_flag = 1;

bool firstMode = true;

float lastX = (float)SCR_WIDTH / 2.0f;
float lastY = (float)SCR_HEIGHT / 2.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_enter_callback(GLFWwindow* window, int entered);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput_GAMESTART(GLFWwindow *window);
void processInput_GAMEACTIVE(GLFWwindow *window);

MainWindow::MainWindow()
{
	success = WindowInit(SCR_WIDTH, SCR_HEIGHT, "Snake");
}
MainWindow::MainWindow(const int width, const int height, const std::string title)
{
	this->success = WindowInit(width, height, title);
}

// 整个Window的初始化
bool MainWindow::WindowInit(const int width, const int height, const std::string title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode * mode = glfwGetVideoMode(monitor);
	window = glfwCreateWindow(mode->width,mode->height, title.c_str(), monitor, NULL);
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
		processInput_GAMESTART(window);
		if (glfwWindowShouldClose(window))
			break;

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SnakeGame.ViewUpdate();
		SnakeGame.ViewRender();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Scene scene;
	SnakeGame.Init(&scene);
	while (!glfwWindowShouldClose(window))
	{
		gameTime.Update();
		processInput_GAMEACTIVE(window);

		glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SnakeGame.FrameCycle();

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

	camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
void processInput_GAMESTART(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
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
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (SnakeGame.BeginFlag < SnakeGame.BeginItemNumber)
			SnakeGame.BeginFlag++;
		else SnakeGame.BeginFlag = 1;
		Sleep(100);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (SnakeGame.BeginFlag >= 1)
			SnakeGame.BeginFlag--;
		else SnakeGame.BeginFlag = SnakeGame.BeginItemNumber;
		Sleep(100);
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
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void processInput_GAMEACTIVE(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		SnakeGame.scene->status = pause;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		SnakeGame.scene->status = normal;
	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
		SnakeGame.scene->snake->speed +=0.1f;
	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
		SnakeGame.scene->snake->speed -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
		camera.MovementSpeed += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
		camera.MovementSpeed -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, gameTime.DeltaTime);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, gameTime.DeltaTime);
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, gameTime.DeltaTime);
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		SnakeGame.scene->snake->Incress();
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		SnakeGame.scene->snake->Decrease();
}