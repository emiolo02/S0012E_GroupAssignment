#pragma once

#include "core/app.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <core/math/mat4.h>
#include "../Material.h"
//#include "../GLTFinfo.h"

struct vertex
{
    vec3 position;
    vec2 UV;
    vec3 normal;
    vec4 tangent;

    vertex()
    {
        this->position = vec3();
        this->UV = vec2();
        this->normal = vec3();
    }
    vertex(vec3 pos, vec2 UV, vec3 normal, vec4 tangent)
    {
        this->position = pos;
        this->UV = UV;
        this->normal = normal;
        this->tangent = tangent;
    }

    bool operator ==(vertex rhs)
    {
        return (this->position == rhs.position &&
            this->UV == rhs.UV &&
            this->normal == rhs.normal);
    }
};

struct Primitive
{
	std::vector<vertex> vertices;

	Material material;
};

class MeshResource
{
public:

	MeshResource();
	//~MeshResource();

	static MeshResource CreateCube(float width, float height, float depth);
	static MeshResource CreateSphere(float radius, int resolution);
	static MeshResource LoadOBJ(std::string path);

	void Upload();
	//void UploadGLTF(GLTFinfo info);
	void Bind();

	std::vector<GLuint> ind;
	std::vector<Primitive> primitives;

private:
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
};