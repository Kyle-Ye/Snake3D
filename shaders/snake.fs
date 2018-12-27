#version 330 core

in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 view;

void main()
{
	vec3 lightPos = vec3(0.0f,-1.0f,0.0f);
	vec3 lightColor = vec3(1.0f,1.0f,1.0f);
	vec3 objectColor = Normal;

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 normalDir = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);	
	float diffuseStrength = max(dot(normalDir,lightDir),0.0f);
	vec3 diffuse = diffuseStrength * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;
	FragColor = vec4(result,1.0f);
}