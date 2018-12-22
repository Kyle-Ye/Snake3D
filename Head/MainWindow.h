#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Head/Scene.h"
#include "../Head/GameObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Head/Shader.h"
#include "../Head/Camera.h"
#include "../Head/Model.h"
#include "../Head/MainWindow.h"
const unsigned int SCR_WIDTH = 960;//1920
const unsigned int SCR_HEIGHT = 540;//1080

class MainWindow
{
public:
	GLFWwindow* window;
	bool success;
	MainWindow();
	MainWindow(const int width, const int height, const std::string title);
	bool WindowInit(const int width, const int height, const std::string title);
	void MainLoop();
	~MainWindow();
};

