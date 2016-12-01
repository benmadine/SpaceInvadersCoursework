//cSprite.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _CSPRITE_H //Includes the code between this and the "#endif"
#define _CSPRITE_H

//Includes
#include "cTextureManager.h" //Takes from the cTextureManager header file
#include "cTexture.h"   //Takes from the cTexture header file

class cSprite
{
private:
	// position
	SDL_Rect spritePos_2D; //Sprite Position
	SDL_Rect spriteDimensions; //Sprite Dimensions
	SDL_Point spriteCentre; //Centre of the Sprite
	FPoint spriteScale; //Scale of the Sprite
	float spriteRotationAngle; //Rotating Sprite
	SDL_Rect boundingRect; //Bounding Rectangle
	bool mActive; //Boolean if active
	SDL_Point spriteTranslation; //Sprite translation

	// Pointer to Sprite Texture
	cTexture* spriteTexture;

	// Texture width & Height
	int textureWidth; //Integar of texure width
	int textureHeight; //Integar of texture height
	float lengthSQRD(SDL_Point theLength);

public:
	cSprite();			// Default constructor
	cSprite(cTexture* theSpriteTexture);			// Default constructor
	~cSprite();			// Destructor
	void render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, FPoint theScaling);
	void render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, double rotAngle, SDL_Point* spriteCentre, FPoint theScaling);
	SDL_Rect getSpritePos();  // Return the sprites current position
	void setSpritePos(SDL_Point sPosition); // set the position of the sprite
	cTexture* getTexture();  // Return the sprites current image
	void setTexture(cTexture* theSpriteTexture);  // set the image of the sprite
	void setSpriteDimensions(int texWidth, int textHeight);
	SDL_Rect getSpriteDimensions(); // Return sprite dimensions
	SDL_Point getSpriteCentre();  // Return the sprites current position
	void setSpriteCentre(SDL_Point sCentre); // set the position of the sprite
	FPoint getSpriteScale();  // Return the sprites scaling factor
	void setSpriteScale(FPoint sScale); // set the sprites scaling factor
	void scaleSprite(); // update the sprites width & height
	float getSpriteRotAngle();  // Return the sprites rotation angle
	void setSpriteRotAngle(float angle); // set the sprites rotation angle
	void setBoundingRect(SDL_Rect pRect);		// Determine the bounding rectangle for the sprite
	SDL_Rect getBoundingRect();		// Get the bounding rectangle for the sprite
	void setActive(bool sActive);			// Set the sprite to active.
	bool isActive();						// Determine if the sprite is active.
	void setSpriteTranslation(SDL_Point spriteTrans);   // Sets the translation for the sprite
	SDL_Point getSpriteTranslation();				 // Gets the sprite translation
	bool collidedWith(SDL_Rect* thisSprite, SDL_Rect* otherSpritePos);	// Check for collisions
	bool SphereSphereCollision(SDL_Point spritePosition, float spriteRadius);
};
#endif