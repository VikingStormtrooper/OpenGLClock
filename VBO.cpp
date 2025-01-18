#include"VBO.h"

// Generates the vertex buffer
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);																	// Generates the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);														// Binds the VBO object and specifies its type
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);							// Defines what and how to store data in the buffer
}

// Binds the vertex buffer
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);														// Binds the VBO object
}

// Unbinds the vertex buffer
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);														// Unbinds the VBO object
}

// Deletes the vertex buffer when it's no longer needed
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);																// Deletes the VBO object
}