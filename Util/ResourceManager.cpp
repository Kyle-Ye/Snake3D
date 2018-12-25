#include "../Head/ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;
std::map<std::string, Model>        ResourceManager::Models;
std::map<std::string, GameObject>   ResourceManager::GameObjects;

void ResourceManager::BindCamera(GameObject &gameObject)
{
	camera.Bind(gameObject);
}

void ResourceManager::UnbindCamera()
{
	//camera.Bind();
}

Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

Shader& ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

Texture2D& ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

Model ResourceManager::LoadModel(const GLchar * file, std::string name,Shader shader)
{
	Models[name] = loadModelFromFile(file,shader);
	return Models[name];
}

Model & ResourceManager::GetModel(std::string name)
{
	return Models[name];
}

GameObject ResourceManager::LoadGameObject(GameObject gameObject, std::string name)
{
	GameObjects[name] = gameObject;
	return GameObjects[name];
}

GameObject & ResourceManager::GetGameObject(std::string name)
{
	return GameObjects[name];
}

void ResourceManager::Clear()
{
	// (Properly) delete all shaders	
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
	// (Properly) delete all textures
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
	// (Properly) delete all models
	for (auto iter : Models)
	{
		for (Mesh* p : iter.second.meshes) {
			delete p;
		}
		std::cout << "The model has been destroyed" << std::endl;
	}
	Shaders.erase(Shaders.begin(), Shaders.end());
	Textures.erase(Textures.begin(), Textures.end());
	Models.erase(Models.begin(), Models.end());
}

void ResourceManager::InitShaderPara(GLuint width, GLuint height)
{
	
}

void ResourceManager::Update()
{
	for (auto iter : Shaders)
	{
		iter.second.SetMatrix4("projection", glm::perspective(glm::radians(camera.Zoom), 16.0f/9.0f, 0.1f, 100.0f));
		iter.second.SetMatrix4("view", camera.GetViewMatrix());
		iter.second.SetVector3f("mColor",0.2,0.3,0.4);
	}
}
void ResourceManager::Render()
{
	for (auto iter : GameObjects)
	{
		iter.second.Draw();
	}
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();
	// 2. Now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
	// Create Texture object
	Texture2D texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	// Load image
	int width, height,nrChannels;
	unsigned char* image = stbi_load(file, &width, &height, &nrChannels,0);
	if (image)
	{
		// Now generate texture
		texture.Generate(width, height, image);
		// And finally free image data
		stbi_image_free(image);
	}
	else
	{
		std::cout << "Failed to load texture1" << std::endl;
	}
	return texture;
}

Model ResourceManager::loadModelFromFile(const GLchar * file,Shader shader)
{
	return Model(file,shader);
}
