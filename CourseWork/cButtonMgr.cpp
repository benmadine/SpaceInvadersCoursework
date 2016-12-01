//cButtonMgr.cpp =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Includes
#include "cButtonMgr.h" //Takes from the cButtonMgr header file
cButtonMgr* cButtonMgr::pInstance = NULL;

//Singleton Design Pattern
cButtonMgr* cButtonMgr::getInstance()
{
	if (pInstance == NULL) //If pInstance is equal to NULL
	{
		pInstance = new cButtonMgr(); //Then makes new button manager
	}
	return cButtonMgr::pInstance; //Returns the button manager
}

//Data Constructor
cButtonMgr::cButtonMgr()
{

}

//Deconstructor
cButtonMgr::~cButtonMgr()
{
	deleteBtn(); //Deletes the button
}

void cButtonMgr::add(LPCSTR btnName, cButton* theBtn)
{
	if (!getBtn(btnName)) //If get button doesnt have a button name
	{
		//cButton * newBtn = new cButton(); //New button equal new button
		//newTxt->loadTexture(theFilename, theSDLRenderer); //NewTxtx loads the texture, gets the filename and the texture
		gameBtns.insert(make_pair(btnName, theBtn)); //Inserts the game button
	}
}

void cButtonMgr::deleteBtn()
{
	for (map<LPCSTR, cButton*>::iterator btn = gameBtns.begin(); btn != gameBtns.end(); ++btn) //For the button to equal the gameButtons, the button does not equal the game buttons, add 1 to button
	{
		delete btn->second; //Deletes the button
	}
}

//Return Texture
cButton* cButtonMgr::getBtn(LPCSTR btnName)    
{
	map<LPCSTR, cButton*>::iterator btn = gameBtns.find(btnName); //Finds the button
	if (btn != gameBtns.end()) //If button does not equal gamebutton
	{
		return btn->second; //Returns the button
	}
	else //Else
	{
		return NULL; //Returns nothing
	}
}
