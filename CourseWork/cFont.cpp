//cFont.cpp =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Includes
#include "cFont.h" //Takes from the cFont header file

//Standard Lib
using namespace std; //Usingf standard libary

//Constructor
cFont::cFont()
{
	theFont = NULL; //Makes the font equal to nothing, its undefined
}

//Deconstructor
cFont::~cFont()
{
	TTF_CloseFont(theFont); //The font
}

//Load Font
bool cFont::loadFont(LPCSTR fontFileName, int fontSize)
{
	theFont = TTF_OpenFont(fontFileName, fontSize); //Makes the font equal to the font file and font size

	if (theFont == NULL) //If the font doesnt have a value already
	{
		cout << " Failed to load font : " << SDL_GetError() << endl; //Displays a message - font didnt load  
		delete theFont; // Delete the font
		return false; //return false value
	}
	cout << "Font '" << fontFileName << "' loaded successfully" << endl; //Displays the font was loaded correctly
	return true; //Returns true
}

//Pointer to font
TTF_Font* cFont::getFont()
{
	return theFont; //Returns the font
}

//Render Text using font
SDL_Texture* cFont::createTextTexture(SDL_Renderer* theRenderer, LPCSTR text, textType txtType, SDL_Color txtColour, SDL_Color txtBkgd)
{
	SDL_Texture* theTxtTexture = NULL; //Makes the text texture undefined, doesnt have a value
	SDL_Surface* theTxtSurface = NULL; //Makes the text surface undefined, doesnt have a value

	//Different types of text backgrounds
	switch (txtType) //Switch between types
	{
	case SOLID: //Solid background colour
	{
		theTxtSurface = TTF_RenderText_Solid(theFont, text, txtColour); //Sets the texture surface 
	}
	break;
	case BLENDED: //Blended background colour
	{
		theTxtSurface = TTF_RenderText_Blended(theFont, text, txtColour); //Sets the texture surface
	}
	break;
	case SHADED: //Shaded backgound colour
	{
		theTxtSurface = TTF_RenderText_Shaded(theFont, text, txtColour, txtBkgd); //Sets the texture surface
	}
	break;
	default:
		break;
	}

	theTxtTexture = SDL_CreateTextureFromSurface(theRenderer, theTxtSurface); //Makes the text texture equal to the texture surface
	SDL_FreeSurface(theTxtSurface); //Texture Surface

	return theTxtTexture; //Returns the text texture
}


