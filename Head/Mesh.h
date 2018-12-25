#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include "Texture2D.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};
struct Texture{
	unsigned int id;
	std::string type;
	std::string path;
};
class Mesh
{
public:
	unsigned int VAO;
	// mesh date
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	// function
	Mesh(std::vector<Vertex> vertices,std::vector<unsigned int>indices,std::vector<Texture> textures);
	~Mesh();
	void Draw(Shader &shader);
private:
	unsigned int VBO, EBO;
	void setupMesh();
};

