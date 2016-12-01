//cTextureManager.cpp =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Includes
#include "cTextureManager.h" //Takes from ctexturemanager header file

cTextureManager* cTextureManager::pInstance = NULL; //Gives an empty value

//Singleton Design Pattern
cTextureManager* cTextureManager::getInstance()
{
	if (pInstance == NULL) //If pInstance is equal to NULL
	{
		pInstance = new cTextureManager(); //Makes pInstance equal to new cTextureManager()
	}
	return cTextureManager::pInstance; //Returns pInstance
}

//Data Constructor
cTextureManager::cTextureManager()
{
	
}

cTextureManager::cTextureManager(SDL_Renderer* theRenderer)
{
	theSDLRenderer = theRenderer; //theSdlRender is equal to theRenderer
}

//Destructor
cTextureManager::~cTextureManager()
{
	deleteTextures(); //Delete textures
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

void cTextureManager::addTexture(LPCSTR txtName, SDL_Texture* theTexture)
{
	if (!getTexture(txtName))
	{
		cTexture * newTxt = new cTexture();
		newTxt->loadTexture(theTexture);
		textureList.insert(make_pair(txtName, newTxt));
	}
}
void cTextureManager::deleteTextures()
{
	for (map<LPCSTR, cTexture*>::iterator txt = textureList.begin(); txt != textureList.end(); ++txt)
	{
		delete txt->second; //Deletes the text
	}
}
void cTextureManager::deleteTexture(LPCSTR txtName)
{
	map<LPCSTR, cTexture*>::iterator txt = textureList.find(txtName); //Makes text equal to the text in the texture list
	this->textureList.erase(txt);
}

//Returns the texture
cTexture* cTextureManager::getTexture(LPCSTR textureName)        // return the texture.
{
	map<LPCSTR, cTexture*>::iterator txt = textureList.find(textureName);
	if (txt != textureList.end()) //If txt does not equal texture list
	{
		return txt->second;
	}
	else
	{
		return NULL; //Return an empty value
	}
}

//Set the renderer
void cTextureManager::setRenderer(SDL_Renderer* ptheRenderer)
{
	this->theSDLRenderer = ptheRenderer;
}