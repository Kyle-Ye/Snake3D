#pragma once

#include<string>
#include<vector>

#include "Shader.h"

class Scene;

class Skybox
{
public:
	Skybox();
	Skybox(std::string path);
	~Skybox();

	void Draw(glm::mat4 view, glm::mat4 projection);

private:
	GLuint loadCubeMap(std::vector<std::string> faces);
	void loadOpenglObject();
	GLuint cubemapTexture;
	GLuint VAO;
	GLuint VBO;
	Shader* shader;
};

