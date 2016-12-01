//cAliens.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _CALIENS_H //Includes the code between this and the "#endif"
#define _CALIENS_H // Ask Please

//Includes
#include "cSprite.h" //Takes from the sprite header file

class cAliens : public cSprite //Current class
{
private: 
	SDL_Point AlienVelocity; //the alien velocity

public:  
	bool jumpedDown;
	cAliens(); //the aliens
	void update(double deltaTime);	 //Update method	
	void setAlienVelocity(SDL_Point alienVel);   //Alien velocity method
	SDL_Point getAlienVelocity();	//gets the alien velocity 
};
#endif