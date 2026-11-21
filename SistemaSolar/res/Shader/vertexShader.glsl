#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;

out vec3 ourColor;
out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
	TexCoords = aTexCoords;
	ourColor = aColor;
	FragPos = vec3(model * vec4(aPos, 1.0f));
	Normal = mat3(transpose(inverse(model))) * normalize(aPos);
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}
