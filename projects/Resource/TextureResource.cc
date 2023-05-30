#include "TextureResource.h"
#include "core/stb_image.h"
#include <iostream>

TextureResource::TextureResource()
{

}

TextureResource::TextureResource(const char* imagePath)
{
	LoadFromFile(imagePath, 0);
}

void
TextureResource::LoadFromFile(const char* imagePath, GLuint index)
{
	this->textures.push_back(Texture());
	textures[textures.size() - 1].index = index;

	glGenTextures(1, &textures[textures.size()-1].id);


	glActiveTexture(GL_TEXTURE0 + textures[textures.size() - 1].index);
	glBindTexture(GL_TEXTURE_2D, textures[textures.size() - 1].id);
	

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// load and generate the texture
	int width, height, nrChannels;
	//stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

//void 
//TextureResource::LoadFromGLTF(GLTFinfo info)
//{
	//glGenTextures(1, &texture);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//
	//// set the texture wrapping/filtering options (on the currently bound texture object)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//
	//// load and generate the texture
	//int width, height, nrChannels;
	//stbi_set_flip_vertically_on_load(true);
	//
	//const uint8_t* data = info.imageInfo.BinaryData;
	//if (data)
	//{
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else
	//{
	//	std::cout << "Failed to load texture" << std::endl;
	//}
//}

void 
TextureResource::BindTexture()
{
	for (int i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + this->textures[i].index);
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}
}

void
TextureResource::UnbindTexture()
{
	for (int i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + this->textures[i].index);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

TextureResource::~TextureResource()
{
	for (int i = 0; i < textures.size(); i++)
		glDeleteTextures(1, &(this->textures[i].id));
}