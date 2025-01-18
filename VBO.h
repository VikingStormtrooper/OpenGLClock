#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

/// <summary>
/// Class for the vertex buffer object.
/// </summary>
class VBO
{
public:
	GLuint ID;
	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif