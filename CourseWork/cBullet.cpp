//cBullet.cpp =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Includes
#include "cBullet.h" //Takes from the CBullet header file

//Constructor
cBullet::cBullet() : cSprite()
{
	this->bulletVelocity = { 0.0, 0.0 }; //Bullet velocity set to 0
}

//Bullet Position
void cBullet::update(double deltaTime)
{

	FPoint direction = { 0.0, 0.0 }; //Floating point direction of the bullet
	direction.X = (sin((this->getSpriteRotAngle())*PI / 180)); //X rotation angle
	direction.Y = -(cos((this->getSpriteRotAngle())*PI / 180)); //Y rotation angle

	direction.X *= this->getSpriteTranslation().x; //Bullets x direction is multiplied by the bullet translation
	direction.Y *= this->getSpriteTranslation().y; //Bullets x direction is multiplied by the bullet translation

	this->bulletVelocity.x = this->bulletVelocity.x + direction.X; //Bullet velocity is eqial to the bullet velocity + the direction it is moving on the x axis
	this->bulletVelocity.y = this->bulletVelocity.y + direction.Y; //Bullet velocity is eqial to the bullet velocity + the direction it is moving on the y axis

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->bulletVelocity.x * deltaTime; //The current position of the sprite on the x axis is adding to and equaling the velocity of the sprite (calculates the new spirte position)
	currentSpritePos.y += this->bulletVelocity.y * deltaTime; //The current position of the sprite on the y axis is adding to and equaling the velocity of the sprite (calculates the new spirte position)

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y }); //Sets the bullet posiiton to the current x and y bullet posotion

	cout << "Bullet position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl; //Displays position of the bullet

	this->setBoundingRect(this->getSpritePos()); //The collision rectangle around the bullet

	if (currentSpritePos.x < 0 || currentSpritePos.x > 975) //If the bullets position is less than 0 or greator than 975 in the x axis
	{
		this->setActive(false); //sets active to false
	}

	if (currentSpritePos.y < 0) //If the bullets position is less than 0 or greator than 700 in the y axis
	{
		this->setActive(false); //Sets active to false
	}
}

//Velocity of the Bullet
void cBullet::setBulletVelocity(SDL_Point bulletVel)
{
	this->bulletVelocity = bulletVel; //Makes bullet velocity equal to bulletVel
}

SDL_Point cBullet::getBulletVelocity()
{
	return this->bulletVelocity; //Returns value of bulletVelocity
}