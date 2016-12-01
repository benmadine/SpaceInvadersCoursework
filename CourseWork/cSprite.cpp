//cSprite.cpp =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Includes
#include "cSprite.h"

// Default constructor
cSprite::cSprite() 			
{
	//Sprite Attributes
	this->spritePos_2D = { 0, 0, 0, 0 };
	this->spriteTexture = NULL; //Spritetexture giving an empty value
	this->spriteCentre = { 0, 0 };
	this->spriteScale = { 1, 1 };
	this->spriteRotationAngle = 0;
	this->boundingRect = { 0, 0, 0, 0 };
	this->mActive = true; //Sets mActive equal to true
	// Sprite Attributes
}

// Default constructor
cSprite::cSprite(cTexture* theSpriteTexture) 			
{
	this->spriteTexture = theSpriteTexture; //Sprite texture
	this->setSpriteDimensions(this->spriteTexture->getTWidth(), this->spriteTexture->getTHeight()); //Height and width of sprite texture
	this->spritePos_2D = { 0, 0, this->spriteTexture->getTWidth(), this->spriteTexture->getTHeight() }; //Position of sprite
	this->spriteCentre = { this->spritePos_2D.w / 2, this->spritePos_2D.h / 2 }; //Sprite centre
	this->spriteScale = { 1, 1 }; //Sprite scale
	this->spriteRotationAngle = 0; //Sprite rotation angle
	this->boundingRect = { 0, 0, 0, 0 }; //Bounding rectangle
	this->mActive = true; //Set active to true
}

// Destructor
cSprite::~cSprite()			
{

}

//Sprites Position
SDL_Rect cSprite::getSpritePos()  
{
	return this->spritePos_2D; //Returns sprite position
}

//Position of the sprite
void cSprite::setSpritePos(SDL_Point sPosition) 
{
	//Sprite position in x and y axis
	this->spritePos_2D.x = sPosition.x;
	this->spritePos_2D.y = sPosition.y;
}

//Sprites current image
cTexture* cSprite::getTexture()  
{
	return this->spriteTexture; //Returns sprite texture
}

//Image of the Sprites
void cSprite::setTexture(cTexture* theSpriteTexture)
{
	//Sprite Images
	this->spriteTexture = theSpriteTexture;
	this->setSpriteDimensions(spriteTexture->getTWidth(), spriteTexture->getTHeight());
	this->spritePos_2D.w = textureWidth;
	this->spritePos_2D.h = textureHeight;
	this->spriteCentre = { this->spritePos_2D.w / 2, this->spritePos_2D.h / 2 };
}


void cSprite::render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, FPoint theScaling)
{
	this->spriteTexture->renderTexture(theRenderer, this->spriteTexture->getTexture(), theSourceRect, theDestRect, theScaling); //Renders the image
}

void cSprite::render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, double rotAngle, SDL_Point* spriteCentre, FPoint theScaling)
{
	this->spriteTexture->renderTexture(theRenderer, this->spriteTexture->getTexture(), theSourceRect, theDestRect, rotAngle, spriteCentre, theScaling); //Renders the image
}

//Sets Sprites Dimensions
void cSprite::setSpriteDimensions(int texWidth, int textHeight)
{
	this->textureWidth = texWidth; //textureWidth
	this->textureHeight = textHeight; //textureHeight
	this->spriteDimensions = { 0, 0, texWidth, textHeight }; //Sprite Dimensions
}

//Gets Sprites Dimensions
SDL_Rect cSprite::getSpriteDimensions()
{
	return this->spriteDimensions; //Return sprite dimensions
}

//Centre of the Sprite
SDL_Point cSprite::getSpriteCentre()  
{
	return this->spriteCentre; //Sprite Centre
}

//Set Sprites Centre
void cSprite::setSpriteCentre(SDL_Point sCentre)  
{
	this->spriteCentre.x = sCentre.x; //Sets sprtie centre in the x axis
	this->spriteCentre.y = sCentre.y; //Sets sprite centre in the y axis
}

//Get Sprite Scaling
FPoint cSprite::getSpriteScale()  
{
	return this->spriteScale;
}

//Set Sprite Scale
void cSprite::setSpriteScale(FPoint sScale)  // set the sprites current scaling
{
	this->spriteScale.X += sScale.X;
	this->spriteScale.Y += sScale.Y;
}

//Update Sprite Scale
void cSprite::scaleSprite() 
{
	// Scale sprite
	this->spritePos_2D.w = this->spriteDimensions.w * this->spriteScale.X;
	this->spritePos_2D.h = this->spriteDimensions.h * this->spriteScale.Y;
	// Scale Sprite Centre for rotation.
	this->spriteCentre.x = this->spritePos_2D.w / 2;
	this->spriteCentre.y = this->spritePos_2D.h / 2;
}

//Sprite Rotation Angle
float cSprite::getSpriteRotAngle() 
{
	return this->spriteRotationAngle;
}

//Sprite Scale
void cSprite::setSpriteRotAngle(float angle)  
{
	this->spriteRotationAngle = angle;
}

//Bounding rectangle
void cSprite::setBoundingRect(SDL_Rect pRect)
{
	SDL_Point sPos = { this->getSpritePos().x, this->getSpritePos().y };
	this->boundingRect = { sPos.x, sPos.y, this->getSpritePos().w, this->getSpritePos().h }; //(pRect, sPos.x - m_Radius, sPos.y - m_Radius, (textureWidth / 2 + sPos.x), (textureHeight / 2 + sPos.y));
}

//Return rectangle
SDL_Rect cSprite::getBoundingRect()	
{
	return cSprite::boundingRect;
}

//Translation for the Sprite
void cSprite::setSpriteTranslation(SDL_Point spriteTrans)
{
	this->spriteTranslation = spriteTrans;
}

//Sprite translation
SDL_Point cSprite::getSpriteTranslation()
{
	return this->spriteTranslation;
}

//Acttivate Sprite
void cSprite::setActive(bool sActive) 		
{
	mActive = sActive;
}

//Check if Sprite is active
bool cSprite::isActive() 	
{
	return mActive;
}

//Collision test
bool cSprite::collidedWith(SDL_Rect* thisSpriteRect, SDL_Rect* otherSpriteRect)
{
	// perform the intersection test
	if (SDL_HasIntersection(thisSpriteRect, otherSpriteRect))
		return true;
	else
		return false;
}

bool cSprite::SphereSphereCollision(SDL_Point spritePosition, float spriteRadius)
{
	SDL_Point theSpriteLen;
	theSpriteLen.x = this->getSpritePos().x - spritePosition.x; //SSprite position - sprite position in the x axis
	theSpriteLen.y = this->getSpritePos().y - spritePosition.y; //SSprite position - sprite position in the y axis
	const float distSq = lengthSQRD(theSpriteLen);

	const float sumRadius = (this->getSpriteCentre().x + spriteRadius);

	if (distSq < sumRadius * sumRadius)
	{
		return true; // Collision
	}
	return false; // No Collision
}

float cSprite::lengthSQRD(SDL_Point theLength)
{
	return (theLength.x * theLength.x) + (theLength.y * theLength.y);
}