#include<glad/glad.h>

/// <summary>
/// Class used to import STL files.
/// </summary>
class STLImporter
{
public:
	GLfloat* ImportXYASCIISTL(const char* filename);
};