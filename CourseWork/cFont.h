//cFont.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _CFONT_H //Includes the code between this and the "#endif"
#define _CFONT_H

//Includes
#include "GameConstants.h"  //Takes from the GameConstants header file

//Standard Lib
using namespace std; //Standard namespace allows cout cin etc...

class cFont
{
private:
	TTF_Font* theFont; //The font variable


public:
	cFont();
	~cFont();
	bool loadFont(LPCSTR fontFileName, int fontSize); //Boolean if loaded font and font size
	TTF_Font* getFont(); //Gets the font
	SDL_Texture* createTextTexture(SDL_Renderer* theRenderer, LPCSTR text, textType txtType, SDL_Color txtColour, SDL_Color txtBkgd); //Textures the font
};
#endif