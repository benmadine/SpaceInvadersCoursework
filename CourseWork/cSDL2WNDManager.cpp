//ccSDL2WNDManager.cpp =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Includes
#include "cSDL2WNDManager.h" //Takes from the cSDL2WNDManager header file

cSDL2WNDManager* cSDL2WNDManager::pInstance = NULL; //Makes pInstance undefined 

//Constructor 
cSDL2WNDManager::cSDL2WNDManager()
{

}

//Singleton Design Pattern
cSDL2WNDManager* cSDL2WNDManager::getInstance()
{
	if (pInstance == NULL) //If pInstance is equal to NULL
	{
		pInstance = new cSDL2WNDManager(); //Makes pInstance equal to new cSDL2WNDManager
	}
	return cSDL2WNDManager::pInstance; //Returns pInstance
}

//Initialise the SDL Context with desired window title string, width and height
bool cSDL2WNDManager::initWND(string strWNDTitle, int iWidth, int iHeight)
{
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0) //If SDL_init is less than 0
	{
		cout << "Failed to init SDL\n"; //Displays console message
		return false; //Returns a false value
	}

	mainWindow = SDL_CreateWindow(strWNDTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		iWidth, iHeight, SDL_WINDOW_OPENGL); //Width and Height of the window

	// Check that everything worked out okay
	if (!mainWindow) 
	{
		cout << "Unable to create window\n"; //Displays message and takes a new line
		CheckSDLError(__LINE__); //Checks erros
		return false; //Returns flase value
	}
	else
	{
		theRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Get the renderer

		if (theRenderer != 0) //If the render doesnt equal 0
		{
			std::cout << "Renderer creation succeeded" << std::endl; //Displays a message and ends the line

			SDL_SetRenderDrawColor(theRenderer, 0, 0, 100, 255); //Render draw colour
		}
		else //Else
		{
			std::cout << "Renderer creation failed" << std::endl; //Displays a message and ends the line
			return false; //Returns a false value
		}
	}

	return true; //Returns a true value
}

void cSDL2WNDManager::CheckSDLError(int line = -1)
{
	string error = SDL_GetError(); //Variable stirng error is equal to SDL_GetError()

	if (error != "") //If error does not equal 
	{
		cout << "SLD Error : " << error << std::endl; //Displays a message of the rror

		if (line != -1) //If the line does not equal to -1
			cout << "\nLine : " << line << std::endl; //Displays the line number and takes a new line

		SDL_ClearError(); //Clears errors
	}
}


SDL_Window* cSDL2WNDManager::getSDLWindow()
{
	return mainWindow;// Returns the mainWindow
}

SDL_GLContext cSDL2WNDManager::getSDL_GLContext()
{
	return mainContext; //Returns the mainContext
}

SDL_Renderer* cSDL2WNDManager::getSDLRenderer()
{
	return theRenderer; //Returns the renderer
}