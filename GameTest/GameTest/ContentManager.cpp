#include "ContentManager.h"
#include <iostream>


ContentManager::ContentManager(int numTextures, string directory){
	textures = new Texture[numTextures];
	textureDir = directory;
	textureIndex = 0;
}

ContentManager::~ContentManager()
{
}

int ContentManager::loadTexture(string textureName, string filePath){
	auto it = loadedTextureMap.find(textureName);

	if (loadedTextureMap.find(textureName) != loadedTextureMap.end()) {
		//if texture with this name has already been loaded from file,
		//then just return id to that texture
		return it->second;
	}else{
		//load texture from file
		textures[textureIndex] = soilLoadTexture(filePath);
		//add texture to map
		loadedTextureMap[textureName] = textureIndex;
		//return texture id, then incremement indexc
		return textureIndex++;
	}
}

int ContentManager::loadTexture(string textureName) {
	auto it = loadedTextureMap.find(textureName);

	if (loadedTextureMap.find(textureName) != loadedTextureMap.end()) {
		//look for texture loaded with this name
		return it->second;
	}

	//could not find texture with name
	printf("could not load texture with name: %s, texture not found", textureName.c_str());
	return -1;
}

bool ContentManager::getTexture(int textureHandle, Texture& outTexture){
	if (textureHandle < 0 || textureHandle > textureIndex) {
		return false;
	}
	

	outTexture = textures[textureHandle];
	return true;
}

void ContentManager::free(){
	delete textures;
	textureIndex = 0;
}



Texture ContentManager::soilLoadTexture(string filePath){
	Texture texture;
	string file = textureDir + filePath;
	texture.glHandle = SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
	return texture;
}
