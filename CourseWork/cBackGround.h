//cBackGround.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _CBKGROUND_H //Includes the code between this and the "#endif"
#define _CBKGROUND_H //Takes from the sprite header file

//Includes
#include "cSprite.h"

class cBackGround : public cSprite
{
public:
	void render();		// Default render function
	void update();		// Update method
};
#endif