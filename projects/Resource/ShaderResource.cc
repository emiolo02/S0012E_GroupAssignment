#include "ShaderResource.h"

ShaderResource::ShaderResource(){}

ShaderResource::ShaderResource(std::string vertShader)
{
	this->program = glCreateProgram();

	ShaderResource::ParseShader(vertShader, GL_VERTEX_SHADER, this->vs);
	ShaderResource::CreateShader(this->vs, this->vertexShader, GL_VERTEX_SHADER, this->program);
}

void
ShaderResource::ParseShader(std::string source, GLuint type, std::string& out)
{
	// Read vert and frag shader and convert to string
	std::ifstream stream(source);

	std::string line;
	std::stringstream sstream;

	while (getline(stream, line))
		sstream << line << '\n';

	if (type == GL_VERTEX_SHADER)
		out = sstream.str();
	
	else if (type == GL_FRAGMENT_SHADER)
		out = sstream.str();
}


GLuint
ShaderResource::CompileShader(GLuint type, const std::string& src)
{
	GLuint id = glCreateShader(type);
	const char* c_src = src.c_str();

	glShaderSource(id, 1, &c_src, NULL);
	glCompileShader(id);

	return id;
}

void
ShaderResource::CreateShader(std::string shaderString, GLuint& shader, GLuint type, GLuint program)
{

	// Create shader
	shader = ShaderResource::CompileShader(type, shaderString);

	// Give shader to GPU
	glAttachShader(program, shader);
}

void ShaderResource::LinkProgram(GLuint program, GLuint vs, GLuint fs)
{
	glLinkProgram(program);
	glValidateProgram(program);

	// Delete intermediates
	glDeleteShader(vs);
	glDeleteShader(fs);
}

void
ShaderResource::Bind(std::string vertSrc, GLuint &program)
{
	

}

void
ShaderResource::ErrorLog(GLuint shader)
{
	GLint shaderLogSize;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(shader, shaderLogSize, NULL, buf);
		printf("[SHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}
}

void 
ShaderResource::Matrix4fv(const char* name, mat4 matrix, GLuint program)
{
	GLuint matLoc = glGetUniformLocation(program, name);
	glUniformMatrix4fv(matLoc, 1, GL_FALSE, value_ptr(matrix));
}

void ShaderResource::Vector4f(const char* name, vec4 v, GLuint program)
{
	GLuint loc = glGetUniformLocation(program, name);
	glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void ShaderResource::Vector3f(const char* name, vec3 v, GLuint program)
{
	GLuint loc = glGetUniformLocation(program, name);
	glUniform3f(loc, v.x, v.y, v.z);
}

void ShaderResource::uFloat(const char* name, float f, GLuint program)
{
	GLuint loc = glGetUniformLocation(program, name);
	glUniform1f(loc, f);
}
