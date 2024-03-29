/******************************************************************************
Class:Shader
Implements:
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Description:VERY simple class to encapsulate GLSL shader loading, linking,
and binding. Useful additions to this class would be overloaded functions to
replace the glUniformxx functions in external code, and possibly a map to store
uniform names and their resulting bindings. 

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////

#pragma once


#include "OGLRenderer.h"

#define SHADER_VERTEX   0
#define SHADER_FRAGMENT 1
#define SHADER_GEOMETRY 2

using namespace std;
class Shader	{
public:
	Shader(string vertex, string fragment , string geometry = "");
	~Shader(void);

	GLuint  GetProgram() { return program;}
	

	void	Reload(bool deleteOld = true);


	bool	LoadSuccess() {
		return !loadFailed;
	}
	bool	LinkProgram();

	bool UsingDefaultShader() const {
		return usingBackupShader;
	}
protected:
	bool	LoadShaderFile(string from, string &into);
	GLuint	GenerateShader(string from, GLenum type);
	void	SetDefaultAttributes();

	void	LoadDefaultShader();
	
	//sets the number of shader files the shader can hold / manage
	GLuint	objects[3];
	GLuint	program;

	bool usingBackupShader;
	bool	loadFailed;

	string	vertexName;
	string	fragName;
	string	geomName;
};

