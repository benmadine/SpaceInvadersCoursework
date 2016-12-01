//cFontMgr.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _CFONTMGR_H //Includes the code between this and the "#endif"
#define _CFONTMGR_H

//Includes
#include "GameConstants.h" //Takes from the GameConstants header file
#include "cFont.h" //Takes from the cFont header file

class cFontMgr
{
private:

	static cFontMgr* pInstance; //Independant instance
	map<LPCSTR, cFont*> fontList;

public:
	static cFontMgr* getInstance();

	cFontMgr();								// Constructor
	~cFontMgr();							// Destructor
	bool initFontLib();						// Initialise the SDL ttf library
	void addFont(LPCSTR fontName, LPCSTR fileName, int fontSize);  // add font to the Font collection
	cFont* getFont(LPCSTR fontName);				// return the font for use
	void deleteFont();								// delete font

};

#endif