//cButton.cpp =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Includes
#include "cButton.h" //Takes from the cButton header file

//Default Constructor
cButton::cButton() : cSprite()
{

}

//Update Sprite Position 
gameState cButton::update(gameState theCurrentGameState, gameState newGameState, SDL_Point theAreaClicked)
{
	SDL_Point areaClicked = theAreaClicked; //The point where the mouse button is clicked
	if (areaClicked.x > this->getSpritePos().x && areaClicked.x < (this->getSpritePos().x + this->getSpriteDimensions().w) && areaClicked.y > this->getSpritePos().y && areaClicked.y < (this->getSpritePos().y + this->getSpriteDimensions().h)) // if the area clicked in the x/y axis is greator than the sprtie positon and if the area clicked in the x/y axis is less than the sprite position plus the sprite dimensions
	{
		this->buttonClickedRC.x = (int)(areaClicked.x - this->getSpritePos().x) / this->getSpriteDimensions().w; //Button clicked is equal to the area clicked minus the sprite position divided by the sprite Dimensions
		this->buttonClickedRC.y = (int)(areaClicked.y - this->getSpritePos().y) / this->getSpriteDimensions().h; //Button clicked is equal to the area clicked minus the sprite position divided by the sprite Dimensions
		this->clicked = true; //changes the value to true when the butotn is clicked
		return newGameState; //returns the new game state
	}
	return theCurrentGameState; //returns the current game state
}

bool cButton::getClicked()
{
	return this->clicked; //Returns if clicked
}
void cButton::setClicked(bool state)
{
	this->clicked = state; //Sets clicked to be a boolean and makes it equal the state
}