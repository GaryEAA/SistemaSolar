#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D textura;
uniform int modo;
uniform int emisivo;
uniform vec3 luzPos;
uniform float brillo;

void main()
{
	if (modo == 1)
	{
		FragColor = vec4(ourColor, 1.0f);
		return;
	}

	vec4 color = texture(textura, TexCoords);

	if (modo == 2)
	{
		FragColor = vec4(color.rgb * brillo, color.a);
		return;
	}

	if (emisivo == 1)
	{
		FragColor = vec4(color.rgb * 1.25f, 1.0f);
		return;
	}

	vec3 N = normalize(Normal);
	vec3 L = normalize(luzPos - FragPos);
	float difusa = max(dot(N, L), 0.0f);
	float luz = 0.07f + 0.93f * difusa;

	FragColor = vec4(color.rgb * luz, 1.0f);
}