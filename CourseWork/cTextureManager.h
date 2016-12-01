//cTextureManager.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _cTextureManager_H //Includes the code between this and the "#endif"
#define _cTextureManager_H

//Includes
#include "GameConstants.h" //Takes from the GameConstants header file
#include "cTexture.h" //Takes from the cTexture header file

class cTextureManager
{
private:
	static cTextureManager* pInstance;
	map<LPCSTR, cTexture*> textureList; //Texture list
	SDL_Renderer* theSDLRenderer; //SDL render

public:
	static cTextureManager* getInstance();
	cTextureManager();
	cTextureManager(SDL_Renderer* theRenderer);
	~cTextureManager();
	void addTexture(LPCSTR txtName, LPCSTR theFilename);		// add the texture for use.
	void addTexture(LPCSTR txtName, SDL_Texture* theTexture);		// add the texture for use.
	cTexture* getTexture(LPCSTR textureName);		// return the texture.
	void setRenderer(SDL_Renderer* ptheRenderer); // Set the renderer
	void deleteTextures();						// Delete all textures;
	void deleteTexture(LPCSTR txtName);						// Delete all textures;
};
#endif