//cSDL2WNDManager.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _SDL2WNDMANAGER_H //Includes the code between this and the "#endif"
#define _SDL2WNDMANAGER_H

//Includes
#include <SDL.h> //Allows
#include <string> //Allows the use of strings
#include <iostream> //Allows the input output

//Using standard libary
using namespace std; 

class cSDL2WNDManager
{
public:
	cSDL2WNDManager();

	bool initWND(string strWNDTitle, int iWidth, int iHeight); //Initialise the SDL Context with desired window title string, width and height
	void CheckSDLError(int line); //Checks errors
	SDL_Window* getSDLWindow(); //Game window
	SDL_GLContext getSDL_GLContext();
	SDL_Renderer* getSDLRenderer(); //Game renders

	static cSDL2WNDManager* getInstance();
	
private:

	static cSDL2WNDManager* pInstance;
	SDL_Window *mainWindow;
	SDL_GLContext mainContext;
	SDL_Renderer* theRenderer;

};

#endif