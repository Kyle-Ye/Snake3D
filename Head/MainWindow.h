#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class MainWindow
{
public:
	MainWindow();
	MainWindow(int width,int height,std::string title);
	WindowInit();
	~MainWindow();
};

