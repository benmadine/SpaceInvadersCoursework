//cTexture.cpp =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Includes
#include "cTexture.h" //Takes from ctexture header file

//Using standard libary
using namespace std;

//Data Constructor
cTexture::cTexture()
{
	cTexture::sdlTextureID = NULL; //Gives an empty value
}

cTexture::cTexture(LPCSTR theFilename, SDL_Renderer *theRenderer)
{
	cTexture::loadTexture(theFilename, theRenderer);
}

//Deconstructor
cTexture::~cTexture()
{
	SDL_DestroyTexture(sdlTextureID);
}

//Creates the texture to use
bool cTexture::loadTexture(LPCSTR theFilename, SDL_Renderer *theRenderer) 	// create the texture for use.
{

	// Call SDL_Image IMG_LoadTexture to create the desired texture
	sdlTextureID = IMG_LoadTexture(theRenderer, theFilename);

	// Check the Texture has been created from the surface
	if (sdlTextureID != 0)
	{
		cout << "Texture '" << theFilename << "' successfully loaded." << endl; //Displays message and ends the line
		SDL_QueryTexture(sdlTextureID, NULL, NULL, &textureWidth, &textureHeight); // determine the width an height of the texture
		return true;
	}
	else
	{
		cout << "Texture '" << theFilename << "' could not be loaded!!" << endl;
		cout << SDL_GetError() << endl;
	}

	return false;
}
bool cTexture::loadTexture(SDL_Texture* theTexture) 	// create the texture for use.
{

	// Call SDL_Image IMG_LoadTexture to create the desired texture
	sdlTextureID = theTexture;

	// Check the Texture has been created from the surface
	if (sdlTextureID != 0)
	{
		cout << "Texture successfully loaded." << endl;
		SDL_QueryTexture(sdlTextureID, NULL, NULL, &textureWidth, &textureHeight); // determine the width an height of the texture
		return true;
	}
	else
	{
		cout << "Texture could not be loaded!!" << endl;
		cout << SDL_GetError() << endl;
	}

	return false;
}

//Returns the texture
SDL_Texture* cTexture::getTexture()        // return the texture.
{
	return cTexture::sdlTextureID;
}

//Return texture width
int cTexture::getTWidth() 						// Return width of texture;
{
	return textureWidth;
}

//Return texture height
int cTexture::getTHeight() 						// Return height of texture;
{
	return textureHeight;
}
//Renders the texture
void cTexture::renderTexture(SDL_Renderer* theRenderer, SDL_Texture* ptheTexture, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, FPoint theScaling)
{
	//SDL_RenderSetScale(theRenderer, theScaling.X, theScaling.Y);
	SDL_RenderCopy(theRenderer, ptheTexture, theSourceRect, theDestRect);
}

void cTexture::renderTexture(SDL_Renderer* theRenderer, SDL_Texture* ptheTexture, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, double rotAngle, SDL_Point* spriteCentre, FPoint theScaling)
{
	//SDL_RenderSetScale(theRenderer, theScaling.X, theScaling.Y);
	SDL_RenderCopyEx(theRenderer, ptheTexture, theSourceRect, theDestRect, rotAngle, spriteCentre, SDL_FLIP_NONE);
}

//Renders the text with the desired font
SDL_Rect cTexture::getTextureRect()
{
	SDL_Rect txtRect = { 0, 0, 0, 0 };
	SDL_QueryTexture(this->sdlTextureID, NULL, NULL, &txtRect.w, &txtRect.h);
	return txtRect;
}