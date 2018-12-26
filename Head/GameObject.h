#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Texture2D.h"
#include "SpriteRenderer2D.h"
#include "Model.h"
enum Tag {
	SNAKE,
	HEAD,
	BODY,
	FOOD,
	WEED,
	MINE,
	DEAD
};
class Scene;

class GameObject
{
public:
	// Object state
	Model *model;
	glm::vec3   position, size;
	glm::mat4   modelMat;
	Tag tag;
	
	GameObject(Scene *scene,Model *model,Tag tag,glm::vec3 pos, glm::vec3 size);
	virtual ~GameObject() = default;
	virtual void Draw();
	virtual void Update();
	virtual void Update(glm::vec3 position);
	virtual void Update(glm::vec3 position,glm::vec3 size);
};