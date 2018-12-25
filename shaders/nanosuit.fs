#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffusel;

void main()
{
	FragColor = texture(texture_diffusel,TexCoords);
}