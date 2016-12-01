//cButtonMgr.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _BUTTONMGR_H //Includes the code between this and the "#endif"
#define _BUTTONMGR_H

//Inlcudes
#include "GameConstants.h" //Takes from the GameConstants header file
#include "cButton.h" //Takes from the button header file

//Standard Lib
using namespace std; //Standard namespace allows cout cin etc...

class cButtonMgr
{
private:
	static cButtonMgr* pInstance; //Makes button independant

protected:
	cButtonMgr(); //Button manager 
	~cButtonMgr();
	map <LPCSTR, cButton*> gameBtns; //Game buttons

public:
	void add(LPCSTR btnName, cButton* theBtn); //Adds button, button name, buttons
	cButton* getBtn(LPCSTR btnName); //Gets the button
	void deleteBtn(); //Delete button
	static cButtonMgr* getInstance(); //Independant
};
#endif