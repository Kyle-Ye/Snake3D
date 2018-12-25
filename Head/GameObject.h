#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer2D.h"
#include "Model.h"
class GameObject
{
public:
	// Object state
	Model *model;
	glm::vec3   Position, Size, Rotation;
	glm::vec3   Color;
	GLfloat     Radian;
	GLboolean   IsSeen;
	GLboolean   Destroyed;
	
	// Constructor(s)
	GameObject();
	GameObject(Model &model);
	GameObject(Model &model,glm::vec3 pos, glm::vec3 size,glm::vec3 color = glm::vec3(1.0f),GLfloat radian = 0.0f,glm::vec3 rotation = glm::vec3(0.0f),GLfloat velocity = 1.0f,GLboolean isSeen = true,GLboolean destroyed = false);
	void Draw();
};