#pragma once
#include "core/app.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "core/math/mat4.h"

class ShaderResource
{
public:
	ShaderResource();
	ShaderResource(std::string vertShader);

	static void Matrix4fv(const char* name, mat4 matrix, GLuint program);
	static void Vector4f(const char* name, vec4 v, GLuint program);
	static void Vector3f(const char* name, vec3 v, GLuint program);
	static void uFloat(const char* name, float f, GLuint program);

	static void Bind(std::string vertSrc, GLuint &program);
	static void CreateShader(std::string shaderString, GLuint &shader, GLuint type, GLuint program);
	static void ParseShader(std::string source, GLuint type, std::string &out);
	static void LinkProgram(GLuint program, GLuint vs, GLuint fs);
	static void ErrorLog(GLuint shader);

	static GLuint CompileShader(GLuint type, const std::string& src);
	
	GLuint program;
	GLuint vertexShader;
	//GLuint fragmentShader;

	std::string vs;
	std::string fs;
};