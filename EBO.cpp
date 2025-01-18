#include"EBO.h"

// Generates the index buffer
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);																	// Generates the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);												// Binds the EBO object and specifies its type
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);					// Defines what and how to store data in the buffer
}

// Binds the index buffer
void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);												// Binds the EBO object
}

// Unbinds the index buffer
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);												// Unbinds the EBO object
}

// Deletes the index buffer when it's no longer needed
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);																// Deletes the EBO object
}