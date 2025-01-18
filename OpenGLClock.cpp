#include<iostream>
#include<ctime>
#include<math.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include"shaderClass.h"
#include"Texture.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

/* -------------------------------------------------------------------------------------------------------------------------
													OpenGL Clock
									Just a small widget to test OpenGL C++ scripting.
------------------------------------------------------------------------------------------------------------------------- */

static void GLFWInitialize(int majorVersion, int minorVersion, int profile);
static void GLFWTerminate(GLFWwindow* window);

/// <summary>
/// Main routine of the application.
/// </summary>
/// <returns>Outcome of the execution of the application</returns>
int main() 
{
	// OpenGL profiles choice to initialize GLFW
	enum class GLFWProfile
	{
		coreProfile = GLFW_OPENGL_CORE_PROFILE,										// Modern OpenGL only
		compatibilityProfile = GLFW_OPENGL_COMPAT_PROFILE							// Modern OpenGL and legacy functions
	};

	// GLFW window parameters
	int const winWidth = 800;														// GLFW window width
	int const winHeight = 800;														// GLFW window height
	const char* winTitle = "OpenGL Clock";											// GLFW window title
	int viewportLeft = 0;															// Left coordinate of the viewport
	int viewportBottom = 0;															// Bottom coordinate of the viewport

	// Initializes GLFW
	GLFWInitialize(3, 3, static_cast<int>(GLFWProfile::coreProfile));				// OpenGL v3.3, core profile

	// Opens the GLFW window
	GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, winTitle, NULL, NULL);
	if (window == NULL)																// Test on the outcome of the GLFW window creation
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();															// Terminates GLFW
		return -1;																	// Exits the application with error
	}
	glfwMakeContextCurrent(window);													// Tells GLFW to use the newly created window
	gladLoadGL();																	// Loads GLAD with the configuration for OpenGL

	// Initializes the viewport (area of the window subject to rendering)
	glViewport(viewportLeft, viewportBottom, winWidth, winHeight);			// Establishes the dimensions and location of the viewport

	// DESCRIPTION OF THE BACKGROUND CIRCLE --------------------------------------------------------------------------------------------------
	// Vertices with position, color, texture data (x, y, z, r, g, b, s, t). GLfloat is larger than the usual C++ float type.
	GLfloat circleVertices[] =
	{
		0.0f,			0.0f,			0.0f,	1.0f,	0.0f,	0.0f,	0.5f,			0.5f,
		0.5f,			0.0f,			0.0f,	1.0f,	0.0f,	0.0f,	1.0f,			0.5f,
		0.475528258f,	0.154508497f,	0.0f,	1.0f,	0.0f,	0.0f,	0.975528258f,	0.654508497f,
		0.404508497f,	0.293892626f,	0.0f,	1.0f,	0.0f,	0.0f,	0.904508497f,	0.793892626f,
		0.293892626f,	0.404508497f,	0.0f,	1.0f,	0.0f,	0.0f,	0.793892626f,	0.904508497f,
		0.154508497f,	0.475528258f,	0.0f,	1.0f,	0.0f,	0.0f,	0.654508497f,	0.975528258f,
		0.0f,			0.5f,			0.0f,	1.0f,	0.0f,	0.0f,	0.5f,			1.0f,
		-0.154508497f,	0.475528258f,	0.0f,	1.0f,	0.0f,	0.0f,	0.345491503f,	0.975528258f,
		-0.293892626f,	0.404508497f,	0.0f,	1.0f,	0.0f,	0.0f,	0.206107374f,	0.904508497f,
		-0.404508497f,	0.293892626f,	0.0f,	1.0f,	0.0f,	0.0f,	0.095491503f,	0.793892626f,
		-0.475528258f,	0.154508497f,	0.0f,	1.0f,	0.0f,	0.0f,	0.024471742f,	0.654508497f,
		-0.5f,			0.0f,			0.0f,	1.0f,	0.0f,	0.0f,	0.0f,			0.5f,
		-0.475528258f,	-0.154508497f,	0.0f,	1.0f,	0.0f,	0.0f,	0.024471742f,	0.345491503f,
		-0.404508497f,	-0.293892626f,	0.0f,	1.0f,	0.0f,	0.0f,	0.095491503f,	0.206107374f,
		-0.293892626f,	-0.404508497f,	0.0f,	1.0f,	0.0f,	0.0f,	0.206107374f,	0.095491503f,
		-0.154508497f,	-0.475528258f,	0.0f,	1.0f,	0.0f,	0.0f,	0.345491503f,	0.024471742f,
		0.0f,			-0.5f,			0.0f,	1.0f,	0.0f,	0.0f,	0.5f,			0.0f,
		0.154508497f,	-0.475528258f,	0.0f,	1.0f,	0.0f,	0.0f,	0.654508497f,	0.024471742f,
		0.293892626f,	-0.404508497f,	0.0f,	1.0f,	0.0f,	0.0f,	0.793892626f,	0.095491503f,
		0.404508497f,	-0.293892626f,	0.0f,	1.0f,	0.0f,	0.0f,	0.904508497f,	0.206107374f,
		0.475528258f,	-0.154508497f,	0.0f,	1.0f,	0.0f,	0.0f,	0.975528258f,	0.345491503
	};
	// Sequence of indices of the vertices to create the required shape. Indices refer to corresponding lines in vertices.
	GLuint circleIndices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		0, 5, 6,
		0, 6, 7,
		0, 7, 8,
		0, 8, 9,
		0, 9, 10,
		0, 10, 11,
		0, 11, 12,
		0, 12, 13,
		0, 13, 14,
		0, 14, 15,
		0, 15, 16,
		0, 16, 17,
		0, 17, 18,
		0, 18, 19,
		0, 19, 20,
		0, 20, 1
	};
	// Creates a new shader program with the default vertex and fragment shaders
	Shader circleShaderProgram("clock.vert", "clock.frag");
	// Creates the array buffer and binds it
	VAO VAO1;																		// Creates the array buffer
	VAO1.Bind();																	// Binds the array buffer
	// Creates the vertex and index buffers
	VBO VBO1(circleVertices, sizeof(circleVertices));								// Creates the vertex buffer with data from circleVertices
	EBO EBO1(circleIndices, sizeof(circleIndices));									// Creates the index buffer with data from circleIndices
	// Links the array buffer to the vertex buffer. The first 3 floats are position data, the following 3 color data
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbinds all buffers to prevent the possibility of accidentally modifying them
	VAO1.Unbind();																	// Unbinds the array buffer
	VBO1.Unbind();																	// Unbinds the vertex buffer
	EBO1.Unbind();																	// Unbinds the index buffer
	// Imports and activates texture
	Texture chessboard("background.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	GLuint uniID = glGetUniformLocation(circleShaderProgram.ID, "scale");			// Gets the location of the "scale" uniform variable
	GLuint uniTex0 = glGetUniformLocation(circleShaderProgram.ID, "tex0");			// Gets the location of the "tex0" uniform variable
	chessboard.texUnit(circleShaderProgram, "tex0", 0);								// Uses "tex0" as texture unit

	// DESCRIPTION OF THE HOUR HAND ----------------------------------------------------------------------------------------------------------
	// Vertices with position, color, texture data (x, y, z, r, g, b, s, t). GLfloat is larger than the usual C++ float type.
	GLfloat hourVertices[] =
	{
		-0.020f,	-0.020f,	0.0f,	1.0f,	1.0f,	1.0f,	0.5f,	0.5f,
		0.020f,		-0.020f,	0.0f,	1.0f,	1.0f,	1.0f,	0.5f,	0.5f,
		0.020f,		0.320f,		0.0f,	1.0f,	1.0f,	1.0f,	0.5f,	0.5f,
		-0.020f,	0.320f,		0.0f,	1.0f,	1.0f,	1.0f,	0.5f,	0.5f
	};
	// Sequence of indices of the vertices to create the required shape. Indices refer to corresponding lines in vertices.
	GLuint hourIndices[] =
	{
		0, 1, 2,
		2, 3, 0
	};
	// Creates a new shader program with the hand vertex and fragment shaders
	Shader hourShaderProgram("hands.vert", "hands.frag");
	// Creates the array buffer and binds it
	VAO VAO2;																		// Creates the array buffer
	VAO2.Bind();																	// Binds the array buffer
	// Creates the vertex and index buffers
	VBO VBO2(hourVertices, sizeof(hourVertices));									// Creates the vertex buffer with data from hourVertices
	EBO EBO2(hourIndices, sizeof(hourIndices));										// Creates the index buffer with data from hourIndices
	// Links the array buffer to the vertex buffer. The first 3 floats are position data, the following 3 color data
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbinds all buffers to prevent the possibility of accidentally modifying them
	VAO2.Unbind();																	// Unbinds the array buffer
	VBO2.Unbind();																	// Unbinds the vertex buffer
	EBO2.Unbind();																	// Unbinds the index buffer
	// Computes the invariant dimensions of the hour hand
	float hourSegmentShort = sqrt(2 * pow(0.02f, 2));								// Length of the short diagonal in the hour hand
	float hourSegmentLong = sqrt(pow(0.02f, 2) + pow(0.32, 2));						// Length of the long diagonal in the hour hand

	// DESCRIPTION OF THE MINUTES HAND -------------------------------------------------------------------------------------------------------
	// Vertices with position, color, texture data (x, y, z, r, g, b, s, t). GLfloat is larger than the usual C++ float type.
	GLfloat minuteVertices[] =
	{
		-0.020f,	-0.020f,	0.0f,	1.0f,	1.0f,	1.0f,	0.5f,	0.5f,
		0.020f,		-0.020f,	0.0f,	1.0f,	1.0f,	1.0f,	0.5f,	0.5f,
		0.020f,		0.400f,		0.0f,	1.0f,	1.0f,	1.0f,	0.5f,	0.5f,
		-0.020f,	0.400f,		0.0f,	1.0f,	1.0f,	1.0f,	0.5f,	0.5f
	};
	// Sequence of indices of the vertices to create the required shape. Indices refer to corresponding lines in vertices.
	GLuint minuteIndices[] =
	{
		0, 1, 2,
		2, 3, 0
	};
	// Creates a new shader program with the hand vertex and fragment shaders
	Shader minuteShaderProgram("hands.vert", "hands.frag");
	// Creates the array buffer and binds it
	VAO VAO3;																		// Creates the array buffer
	VAO3.Bind();																	// Binds the array buffer
	// Creates the vertex and index buffers
	VBO VBO3(minuteVertices, sizeof(minuteVertices));								// Creates the vertex buffer with data from minuteVertices
	EBO EBO3(minuteIndices, sizeof(minuteIndices));									// Creates the index buffer with data from minuteIndices
	// Links the array buffer to the vertex buffer. The first 3 floats are position data, the following 3 color data
	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbinds all buffers to prevent the possibility of accidentally modifying them
	VAO3.Unbind();																	// Unbinds the array buffer
	VBO3.Unbind();																	// Unbinds the vertex buffer
	EBO3.Unbind();																	// Unbinds the index buffer
	// Computes the invariant dimensions of the hour hand
	float minuteSegmentShort = sqrt(2 * pow(0.02f, 2));								// Length of the short diagonal in the minute hand
	float minuteSegmentLong = sqrt(pow(0.02f, 2) + pow(0.40, 2));					// Length of the long diagonal in the minute hand

	// RENDERING CYCLE -----------------------------------------------------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window))											// Checks for events which could close the window
	{
		// Retrieves the current local time
		time_t now;																	// Current time in time_t form
		struct tm datetime;															// Current time in tm form
		now = time(NULL);															// Gets the current time
		localtime_s(&datetime, &now);												// Converts time_t to tm according to the local time
		int hour = datetime.tm_hour;												// Current hour
		int minutes = datetime.tm_min;												// Current minutes
		if (hour > 12)
			hour -= 12;																// Converts hour from 24h format to 12h format
		float alpha = 2 * 3.14159f * hour / 12;										// Rotation of the hand in 1 hour (rad)
		float beta = atan(1);														// Angle of the short diagonal at time = 0 hours
		float gamma = atan(0.02 / 0.32);											// Angle of the long hour diagonal at time = 0 hours
		float delta = atan(0.02 / 0.40);											// Angle of the long minute diagonal at time = 0 hours
		float epsilon = 2 * 3.14159f * minutes / 60;								// Rotation of the hand in 1 minute (rad)
		// Calculates the new shape of the hour hand
		hourVertices[0] = hourSegmentShort * -sin(beta + alpha);
		hourVertices[1] = hourSegmentShort * -cos(beta + alpha);
		hourVertices[8] = hourSegmentShort * sin(beta - alpha);
		hourVertices[9] = hourSegmentShort * -cos(beta - alpha);
		hourVertices[16] = hourSegmentLong * sin(gamma + alpha);
		hourVertices[17] = hourSegmentLong * cos(gamma + alpha);
		hourVertices[24] = hourSegmentLong * -sin(gamma - alpha);
		hourVertices[25] = hourSegmentLong * cos(gamma - alpha);
		// Calculates the new shape of the minutes hand
		minuteVertices[0] = minuteSegmentShort * -sin(beta + epsilon);
		minuteVertices[1] = minuteSegmentShort * -cos(beta + epsilon);
		minuteVertices[8] = minuteSegmentShort * sin(beta - epsilon);
		minuteVertices[9] = minuteSegmentShort * -cos(beta - epsilon);
		minuteVertices[16] = minuteSegmentLong * sin(delta + epsilon);
		minuteVertices[17] = minuteSegmentLong * cos(delta + epsilon);
		minuteVertices[24] = minuteSegmentLong * -sin(delta - epsilon);
		minuteVertices[25] = minuteSegmentLong * cos(delta - epsilon);
		// Binds the array buffer and updates the vertex buffer
		VAO2.Bind();																// Binds the array buffer
		VBO VBO2(hourVertices, sizeof(hourVertices));								// Populates the vertex buffer with updated data
		// Links the array buffer to the vertex buffer. The first 3 floats are position data, the following 3 color data
		VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		// Unbinds all buffers to prevent the possibility of accidentally modifying them
		VAO2.Unbind();
		VBO2.Unbind();
		EBO2.Unbind();
		// Binds the array buffer and updates the vertex buffer
		VAO3.Bind();																// Binds the array buffer
		VBO VBO3(minuteVertices, sizeof(minuteVertices));							// Populates the vertex buffer with updated data
		// Links the array buffer to the vertex buffer. The first 3 floats are position data, the following 3 color data
		VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		// Unbinds all buffers to prevent the possibility of accidentally modifying them
		VAO3.Unbind();
		VBO3.Unbind();
		EBO3.Unbind();
		// Performs the drawings
		glClearColor(1.0f, 0.79f, 0.05f, 1.0f);										// Chooses a color for the background
		glClear(GL_COLOR_BUFFER_BIT);												// Applies the background color
		glUniform1f(uniID, 1.0f);													// Applies scale
		chessboard.Bind();															// Binds texture
		VAO1.Bind();																// Binds the array buffer for the circle
		glDrawElements(GL_TRIANGLES, sizeof(circleIndices), GL_UNSIGNED_INT, 0);	// Primitive to draw with the given indices and index 0
		VAO2.Bind();																// Binds the array buffer for the hour hand
		glDrawElements(GL_TRIANGLES, sizeof(hourIndices), GL_UNSIGNED_INT, 0);		// Primitive to draw with the given indices and index 0
		VAO3.Bind();																// Binds the array buffer for the hour hand
		glDrawElements(GL_TRIANGLES, sizeof(minuteIndices), GL_UNSIGNED_INT, 0);	// Primitive to draw with the given indices and index 0
		glfwSwapBuffers(window);													// Swaps the back and front buffers of the window
		glfwPollEvents();															// Processes all events in queue
	}

	// Deletes buffers and program after using them
	VAO1.Delete();																	// Deletes the array buffer
	VBO1.Delete();																	// Deletes the vertex buffer
	EBO1.Delete();																	// Deletes the index buffer
	chessboard.Delete();															// Deletes the texture
	circleShaderProgram.Delete();													// Deletes the shader program
	VAO2.Delete();																	// Deletes the array buffer
	VBO2.Delete();																	// Deletes the vertex buffer
	EBO2.Delete();																	// Deletes the index buffer
	hourShaderProgram.Delete();														// Deletes the shader program
	VAO3.Delete();																	// Deletes the array buffer
	VBO3.Delete();																	// Deletes the vertex buffer
	EBO3.Delete();																	// Deletes the index buffer
	minuteShaderProgram.Delete();													// Deletes the shader program

	// Terminates GLFW and destroys the window object
	GLFWTerminate(window);															// Terminates the GLFW window
	return 0;																		// Exits the application with no errors
}

/// <summary>
/// Initializes GLFW to be able to use its functions.
/// </summary>
/// <param name="majorVersion">Major version of OpenGL</param>
/// <param name="minorVersion">Minor version of OpenGL</param>
static void GLFWInitialize(int majorVersion, int minorVersion, int profile)
{
	glfwInit();																		// Initializes GLFW to be able to use its functions
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);						// Tells the major version to GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);						// Tells the minor version to GLFW
	glfwWindowHint(GLFW_OPENGL_PROFILE, profile);									// Core profile includes only the modern version of OpenGL
}

/// <summary>
/// Terminates GLFW at the end of the program.
/// </summary>
/// <param name="window">The OpenGL window to close</param>
static void GLFWTerminate(GLFWwindow* window)
{
	glfwDestroyWindow(window);														// Destroys the window object
	glfwTerminate();																// Terminates GLFW after using it
}