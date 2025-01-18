#include"shaderClass.h"

// Reads the content of the shader files
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Generates the shader
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Initializes vertex and fragment codes to the content of the given input files
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);
	// Converts the content of the input files to an array of char
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();
	// Creates a vertex shader object and compiles it
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");
	// Creates a fragment shader object and compiles it
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");
	// Creates a shader program from the vertex and fragment shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");
	// Deletes the vertex and fragment shaders after using them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

/// <summary>
/// Uses a previously created shader program.
/// </summary>
void Shader::Activate()
{
	glUseProgram(ID);
}

/// <summary>
/// Deletes the shader program when it's no longer needed.
/// </summary>
void Shader::Delete()
{
	glDeleteProgram(ID);				
}

/// <summary>
/// Provides information about shader compilation and linking errors.
/// </summary>
/// <param name="shader">The shader ID to investigate</param>
/// <param name="type">The type of shader which is affected by an error</param>
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)									
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
		}
	}
	else														
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)											
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
		}
	}
}