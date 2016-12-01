//cBullet.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _CBULLET_H //Includes the code between this and the "#endif"
#define _CBULLET_H

//Includes
#include "cSprite.h" //Takes from the sprite header file


class cBullet : public cSprite //Current class
{
private:
	SDL_Point bulletVelocity; //bullet velocity

public:
	cBullet();
	void update(double deltaTime);		// Bullet update method
	void setBulletVelocity(SDL_Point bulletVel);   // Sets the velocity for the Bullet
	SDL_Point getBulletVelocity();				 // Gets the Bullet velocity
};
#endif