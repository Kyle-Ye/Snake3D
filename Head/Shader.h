#pragma once
#include <glad/glad.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	unsigned int ID;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
	void Enable();
	void Disable();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec3(const std::string & name, glm::vec3 &vector) const;
	void setVec4(const std::string & name, glm::vec4 &vector) const;
	void setMat4(const std::string & name,glm::mat4 &trans) const;
private:
	void checkCompileErrors(unsigned int shader, std::string type);
};