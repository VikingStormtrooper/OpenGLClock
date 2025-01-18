#include"Texture.h"

/// <summary>
/// Imports and activates a texture.
/// </summary>
/// <param name="image"></param>
/// <param name="texType"></param>
/// <param name="slot"></param>
/// <param name="format"></param>
/// <param name="pixelType"></param>
Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType;
	int widthImg, heightImg, numColCh;										// Dimensions and number of channel colors of the texture
	stbi_set_flip_vertically_on_load(true);									// Flips the image since otherwise it is upside-down
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &ID);													// Generates texture from the imported image
	glActiveTexture(slot);													// Sets the active texture slot
	glBindTexture(texType, ID);												// Binds the new texture to the active slot
	// Sets texture parameters
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);			// Keeps the nearest image rendering (best for pixel art)
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);			// Keeps the nearest image rendering (best for pixel art)

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);					// Repeats the image along the S axis
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);					// Repeats the image along the T axis

	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);												// Creates mipmaps (smaller resolution versions)

	stbi_image_free(bytes);													// Clears memory from the image bytes
	glBindTexture(texType, 0);												// Unbinds the texture to prevent accidental modifications
}

// Applies the texture
void Texture::texUnit(Shader shader, const char* uniform, GLuint unit)
{
	GLuint uniTex = glGetUniformLocation(shader.ID, uniform);				// Gets the location of the uniform variable
	shader.Activate();														// Activates the shader program
	glUniform1i(uniTex, unit);												// Applies the texture
}

// Binds the texture
void Texture::Bind()
{
	glBindTexture(type, ID);												// Binds texture
}

// Unbinds the texture
void Texture::Unbind()
{
	glBindTexture(type, 0);													// Unbinds texture
}

// Deletes the texture
void Texture::Delete()
{
	glDeleteTextures(1, &ID);												// Deletes the texture
}