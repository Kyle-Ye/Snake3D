#pragma once
#include <map>
#include <string>
#include <glad/glad.h>
#include "Shader.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Model.h"
#include "GameObject.h"
// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined.
class ResourceManager
{
public:
	// Resource storage
	static std::map<std::string, Shader>    Shaders;
	static std::map<std::string, Texture2D> Textures;
	static std::map<std::string, Model> Models;
	static std::map<std::string, GameObject> GameObjects;
	static Camera camera;

	static void BindCamera(GameObject &gameObject);
	static void UnbindCamera();

	static Shader   LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
	static Shader&  GetShader(std::string name);

	static Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
	static Texture2D& GetTexture(std::string name);

	static Model LoadModel(const GLchar *file, std::string name, Shader shader);
	static Model& GetModel(std::string name);

	static GameObject LoadGameObject(GameObject gameObject, std::string name);
	static GameObject& GetGameObject(std::string name);

	static void      Clear();
	static void      InitShaderPara(GLuint width,GLuint height);
	static void      UpdateShaderPosition();
private:
	// Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
	ResourceManager() { }
	static Shader    loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
	static Model loadModelFromFile(const GLchar *file, Shader shader);
};