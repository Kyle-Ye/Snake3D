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
	glm::vec3   Position, Size;
	GLboolean   IsSeen;
	GLboolean   Destroyed;
	
	// Constructor(s)
	GameObject();
	GameObject(Model &model);
	GameObject(Model &model,glm::vec3 pos, glm::vec3 size,GLboolean isSeen = true,GLboolean destroyed = false);
	void Draw();
};