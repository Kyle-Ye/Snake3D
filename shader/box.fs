#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture_1;
uniform sampler2D ourTexture_2;
uniform float visibility;

void main()
{
	FragColor = mix(texture(ourTexture_1,TexCoord),texture(ourTexture_2,TexCoord),visibility);
}