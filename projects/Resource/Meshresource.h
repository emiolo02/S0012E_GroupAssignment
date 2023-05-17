#pragma once

#include "core/app.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <core/math/mat4.h>
#include "../GLTFinfo.h"

class MeshResource
{
public:

	MeshResource();
	//~MeshResource();

	static MeshResource CreateCube(float width, float height, float depth);
	static MeshResource CreateSphere(float radius, int resolution);
	static MeshResource LoadOBJ(std::string path);
	static MeshResource LoadOBJ(std::string path, std::string& outTexPath);

	void Upload();
	void UploadGLTF(GLTFinfo info);
	void Bind();

	std::vector<GLuint> ind;
	std::vector<Primitive> primitives;

private:
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
};