//cButton.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _CBUTTON_H //Includes the code between this and the "#endif"
#define _CBUTTON_H

//Includes
#include "cSprite.h" //Takes from the sprite header file 

class cButton : public cSprite
{

private:

	SDL_Point buttonClickedRC; //Button clicked
	bool clicked = false; //boolean set to false when nothing clicked

public:
	cButton(); //button

	gameState update(gameState theCurrentGameState, gameState newGameState, SDL_Point theAreaClicked); //changes the current gamestate

	bool getClicked(); //boolean get clicked true/false
	void setClicked(bool state); //clicked change value 

};
#endif