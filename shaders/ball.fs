#version 330 core
in vec2 TexCoords;
out vec4 color;
uniform vec3 mColor;

void main()
{
	color = vec4(mColor,1.0f);
}