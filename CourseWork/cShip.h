//cShip.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _CSHIP_H //Includes the code between this and the "#endif"
#define _CSHIP_H

//Inlcudes
#include "cSprite.h" //Takes from the sprite header file

class cShip : public cSprite
{
private:
	SDL_Point shipVelocity; //Ship Velocity

public:
	cShip();
	void update(double deltaTime);		// Ship update method
	void setShipVelocity(SDL_Point shipVel);   // Sets the velocity for the ship
	SDL_Point getShipVelocity();				 // Gets the ship velocity
};
#endif