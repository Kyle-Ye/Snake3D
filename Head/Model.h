#pragma once
#include <assimp/scene.h>
#include "Shader.h"
#include "Mesh.h"
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Texture2D.h"


class Model
{
friend class ResourceManager;
public:
	Model();
	Model(const GLchar * path,Shader shader);
	void Draw();// draws the model, and thus all its meshes
private:
	Shader shader;
	// Model Data
	// ----------

	std::vector<Mesh*> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	
	// Functions
	// ---------
	void loadModel(std::string const &path); // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void processNode(aiNode *node,const aiScene *scene);
	Mesh* processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(std::string const &path, const std::string &directory, bool gamma = false);
};

