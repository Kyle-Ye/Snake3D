#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
class Texture2D
{
public:
	// Holds the ID of the texture object, used for all texture operations to reference to this particular texture
	GLuint ID;

	// Texture image dimensions
	GLuint Width, Height; // Width and height of loaded image in pixels

	// Texture Format
	GLuint Internal_Format; // Format of texture object
	GLuint Image_Format; // Format of loaded image

	// Texture configuration
	GLuint Wrap_S; // Wrapping mode on S axis
	GLuint Wrap_T; // Wrapping mode on T axis
	GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
	GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels

	// Constructor (sets default texture modes)
	Texture2D();

	// Generates texture from image data
	void Generate(GLuint width, GLuint height, unsigned char* data);

	// Binds the texture as the current active GL_TEXTURE_2D texture object
	void Bind() const;
};
