//cBackGround.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Includes
#include "cTextureManager.h"
cTextureManager* cTextureManager::pInstance = NULL;

//Singleton Design Pattern
cTextureManager* cTextureManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cTextureManager();
	}
	return cTextureManager::pInstance;
}

//Data Constructor
cTextureManager::cTextureManager()
{

}

cTextureManager::cTextureManager(SDL_Renderer* theRenderer)
{
	theSDLRenderer = theRenderer;
}

//Destructor
cTextureManager::~cTextureManager()
{

}

void cTextureManager::addTexture(LPCSTR txtName, LPCSTR theFilename)
{
	if (!getTexture(txtName))
	{
		cTexture * newTxt = new cTexture();
		newTxt->loadTexture(theFilename, theSDLRenderer);
		textureList.insert(make_pair(txtName, newTxt));
	}
}

void cTextureManager::deleteTextures()
{
	for (map<LPCSTR, cTexture*>::iterator txt = textureList.begin(); txt != textureList.end(); ++txt)
	{
		delete txt->second;
	}
}

//Returns the texture
cTexture* cTextureManager::getTexture(LPCSTR textureName)
{
	map<LPCSTR, cTexture*>::iterator txt = textureList.find(textureName);
	if (txt != textureList.end())
	{
		return txt->second;
	}
	else
	{
		return NULL;
	}
}

//Sets the Renderer
void cTextureManager::setRenderer(SDL_Renderer* ptheRenderer)
{
	this->theSDLRenderer = ptheRenderer;
}