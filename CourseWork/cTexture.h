//cTexture.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _CTEXTURE_H //Includes the code between this and the "#endif"
#define _CTEXTURE_H

//Includes
#include "GameConstants.h" //Takes from the GameConstants header file

class cTexture
{
private:
	SDL_Texture* sdlTextureID;
	int textureWidth; //Integar Texture Width
	int textureHeight; //Integar texture Height


public:
	cTexture();
	cTexture(LPCSTR theFilename, SDL_Renderer *theRenderer);
	~cTexture();
	bool loadTexture(LPCSTR theFilename, SDL_Renderer *theRenderer);		// create the texture for use.
	bool loadTexture(SDL_Texture* theTexture);		// create the texture for use.
	void renderTexture(SDL_Renderer* theRenderer, SDL_Texture* ptheTexture, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, FPoint theScaling);
	void renderTexture(SDL_Renderer* theRenderer, SDL_Texture* ptheTexture, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, double rotAngle, SDL_Point* spriteCentre, FPoint theScaling);
	SDL_Texture* getTexture();						// return the texture.
	int getTWidth();						// Return width of texture;
	int getTHeight();						// Return height of texture;
	SDL_Rect getTextureRect(); // get Texture dimensions
};
#endif