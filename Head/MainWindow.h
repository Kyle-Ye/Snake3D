#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

