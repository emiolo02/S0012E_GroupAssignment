#pragma once
#include "core/app.h"
#include <vector>

class TextureResource
{
public:
	struct Texture
	{
		GLuint id;
		GLuint index;
	};

	TextureResource();
	TextureResource(const char* imagePath);

	void LoadFromFile(const char* imagePath, GLuint index);
	//void LoadFromGLTF(GLTFinfo info);

	void BindTexture();
	void UnbindTexture();


	~TextureResource();
private:
	//unsigned char* data;
	std::vector<Texture> textures;
};