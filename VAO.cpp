#include"VAO.h"

// Generates the array buffer
VAO::VAO()
{
	glGenVertexArrays(1, &ID);																// Generates the array buffer
}

// Links the vertex array to the vertex buffer
void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();																				// Binds the VAO object
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);			// Index layout, 3D vertices as floats
	glEnableVertexAttribArray(layout);														// Enables the attributes which are at position layout
	VBO.Unbind();																			// Unbinds the VAO object
}

// Binds the array buffer
void VAO::Bind()
{
	glBindVertexArray(ID);																	// Binds the VAO object
}

// Unbinds the array buffer
void VAO::Unbind()
{
	glBindVertexArray(0);																	// Unbinds the VAO object
}

// Deletes the vertex array when it's no longer needed
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);															// Deletes the VAO object
}