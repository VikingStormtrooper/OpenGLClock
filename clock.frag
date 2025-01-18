#version 330 core
out vec4 FragColor;
in vec3 color;										// Inputs the color from the vertex shader
in vec2 texCoord;
uniform sampler2D tex0;
void main()
{
	vec2 crd = vec2(texCoord.x, texCoord.y);
	//FragColor = vec4(color, 1.0f);
	FragColor = texture(tex0, crd);
}