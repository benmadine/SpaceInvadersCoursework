//cAliens.cpp =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Includes
#include "cAliens.h" //Takes from the cAlien header file

//Default Constructor
cAliens::cAliens() : cSprite()
{
	this->AlienVelocity = { 0.0, 0.0 }; //The Alien velocity
}

//Sprites Position
void cAliens::update(double deltaTime)
{
	bool jumpedDown = false; //Boolean if the alien has hit the side of the screen

	SDL_Rect currentSpritePos = this->getSpritePos(); //Current alien position
	currentSpritePos.x += this->getSpriteTranslation().x * deltaTime; //The current position of the sprite on the x axis is adding to and equaling the velocity of the sprite (calculates the new spirte position)
	currentSpritePos.y += this->getSpriteTranslation().y * deltaTime; //The current position of the sprite on the y axis is adding to and equaling the velocity of the sprite (calculates the new spirte position)

	this->AlienVelocity = { 0, 0 }; //Alien velocity set to 0 in both axis

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y }); //Sprite position is the current x and y posiiton calculated above 
	cout << "Alien position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl; //Shows the position in the console window
	this->setBoundingRect(this->getSpritePos()); //The collision rectangle around the sprite

	if (currentSpritePos.x > 900 && currentSpritePos.x != 0) //If the aliens x value is less than 975
		{
			//this->setAlienVelocity({ -1, 0 }); //Set the alien velocity to -1, moves the alien left
			this->setSpritePos({ this->getSpritePos().x - 10, this->getSpritePos().y + 150 }); // Moves the alien to the correct positon once after it moves down
			this->setSpriteTranslation({ -10, 0 }); //Set the alien velocity to -1, moves the alien left
		}
	
	if (currentSpritePos.x == 0) //If alien positon is equal to 0
		{
			cout << "Im at the wall wooo and going to move down"; //Displays message that the alien is going to move down
			this->setSpritePos({ this->getSpritePos().x + 10, this->getSpritePos().y + 150 });  // Moves the alien to the correct positon once after it moves down
			this->setAlienVelocity({ +100, 0 }); //Sets the alien velocity to + 1, moves right
			this->setSpriteTranslation({ 100, 0 }); //Set the alien velocity to -1, moves the alien left
		}
	if (currentSpritePos.y == 600)
	{
		cout << "Im at 600 do we beat him now?";
	}
}

//The alien velocity 
void cAliens::setAlienVelocity(SDL_Point AlienVel)
{
	AlienVelocity = AlienVel; //alien velocity is equal to alienVel
}

SDL_Point cAliens::getAlienVelocity()
{
	return AlienVelocity; //returns the alien velocity 
}