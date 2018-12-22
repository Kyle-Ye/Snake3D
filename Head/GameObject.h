#pragma once
#include "Scene.h"
class GameObject
{
	friend class Scene;
public:
	GameObject(Scene *scene, Shader *shader, Model *model);
	GameObject(Scene *scene, Shader *shader, float *vectices, int size);
	~GameObject();
protected:
	
	float *vertices;
	int size;
	Scene *scene;	
	Shader *shader;
	Model *model;							
	GameObject *parent;							
	std::list<GameObject*> childrenList;		

	bool isRendereringEnable = true;
	bool isPreActive;
	bool isActivity;

};

