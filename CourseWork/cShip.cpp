//cShip.cpp =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Includes
#include "cShip.h" //Takes from the cFontMgr header file

//Constructor
cShip::cShip() : cSprite()
{
	this->shipVelocity = { 0.0f, 0.0f }; //Ships velocity set to (0,0)
}

//Sprite Position
void cShip::update(double deltaTime)
{
	SDL_Rect currentSpritePos = this->getSpritePos(); //Current sprite position is equal to getSpritePos

	currentSpritePos.x += shipVelocity.x; //CurrentSprite Pos is equal and adding from the shipVelocity in the x axis
	currentSpritePos.y += shipVelocity.y; //CurrentSprite Pos is equal and adding from the shipVelocity in the y axis

	this->shipVelocity = { 0, 0 }; //Ships velocity set to (0,0)

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y }); //Setting the sprite position to the current sprite position in the x and y axis
	this->setBoundingRect(this->getSpritePos()); //Sets the bounding rectangle to the sprite position

	if (currentSpritePos.x < 0 || currentSpritePos.x > 975) //If the sprites position is less than 0 or greator than 975 in the x axis
	{
		this->setSpriteTranslation({ 0, 0 }); //Sets sprite translation to 0
	}

	if (currentSpritePos.y < 0 || currentSpritePos.y > 700) //If the sprites position is less than 0 or greator than 700 in the y axis 
	{
		this->setSpriteTranslation({ 0, 0 }); //Sets sprite translation to 0
	}
}

//Ship Velocity
void cShip::setShipVelocity(SDL_Point shipVel)
{
	shipVelocity = shipVel; //Ships velocity is equal to ShipVel
}

SDL_Point cShip::getShipVelocity()
{
	return shipVelocity; //Returns the ship velocity
}