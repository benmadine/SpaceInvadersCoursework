//CFontMgr.cpp =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Includes
#include "cFontMgr.h" //Takes from the cFontMgr header file

cFontMgr* cFontMgr::pInstance = NULL; //Makes pInstance undefined 

//Singleton design pattern
cFontMgr* cFontMgr::getInstance()
{
	if (pInstance == NULL) //If pInstance is equal to NULL
	{
		pInstance = new cFontMgr(); //Makes pInstance equal to new cFontMgr()
	}
	return cFontMgr::pInstance; //Returns pInstance
}

//Constructor
cFontMgr::cFontMgr()
{

}

//Destructor
cFontMgr::~cFontMgr()							
{
	deleteFont(); //Deletes the font
	TTF_Quit(); //True type font quit
}

bool cFontMgr::initFontLib()
{
	// Initialize SDL_ttf library
	if (TTF_Init() != 0) //If TTF_Init does not equal 0
	{
		cout << "TTF_Init() Failed: " << SDL_GetError() << endl; //Displays message and take a new line
		return false; //Returns a false value
	}
	else //Else
	{
		return true; //Returns a true value
	}
}

void cFontMgr::addFont(LPCSTR fontName, LPCSTR fileName, int fontSize)  // add font to the Font collection
{
	if (!getFont(fontName)) //If get font doesnt have a font name
	{
		cFont * newFont = new cFont(); //New font 
		newFont->loadFont(fileName, fontSize);  //The new font loads the font with  selected font and size
		fontList.insert(make_pair(fontName, newFont)); //Inserts the fonts from the font list
	}
}

// Return the font for use
cFont* cFontMgr::getFont(LPCSTR fontName) 
{
	map<LPCSTR, cFont*>::iterator theFont = fontList.find(fontName); //The font equals the font from the fontlist 
	if (theFont != fontList.end()) //If the font does not equal to one on the list
	{
		return theFont->second; // Returns the font
	}
	else //Else
	{
		return NULL; //Returns a empty value
	}
}

//Deletes the font
void cFontMgr::deleteFont()	
{
	for (map<LPCSTR, cFont*>::const_iterator theFont = fontList.begin(); theFont != fontList.end(); theFont++) //If the font equals font list - begin. If the font doesnt not equal font list - end. Add one to theFont
	{
		//TTF_CloseFont(theFont->second->getFont());
		delete theFont->second; //Deletes the font
	}
}