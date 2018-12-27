#pragma once
#include "../Head/GameObject.h"

class Weed
	:public GameObject
{
public:
	Weed(Scene *scene, Model *model, Tag tag, glm::vec3 pos, glm::vec3 size);
	~Weed();
	void Draw() override;
};

