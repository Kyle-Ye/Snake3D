#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D ball_image;
uniform vec3 mColor;

void main()
{
	vec4 aColor = vec4(mColor, 1.0) * texture(ball_image, TexCoords);
	if(aColor.a < 0.01)
		discard;
    color = aColor;
}