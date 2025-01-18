#version 330 core
out vec4 FragColor;
in vec3 color;										// Inputs the color from the vertex shader
void main()
{
	FragColor = vec4(color, 1.0f);
}