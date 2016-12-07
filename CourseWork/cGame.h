//cGame.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _GAME_H  //Includes the code between this and the "#endif"
#define _GAME_H

//Includes
#include <SDL.h> //Takes from the SDL header file
#include "spaceInvadersGame.h" //Takes from the SpaceInvadersGame header file

//Standard Lib
using namespace std; //Standard namespace allows cout cin etc...

class cGame
{
public:
	cGame();

	void initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer); //Initialise method
	void run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer); //Run method
	void cleanUp(SDL_Window* theSDLWND); //Cleanup method
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer); //Render method
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre); //Render method
	void update(); //Update method
	void update(double deltaTime); //Update method
	bool getInput(bool theLoop); //Boolean getInput
	double getElapsedSeconds(); //Gets seconds in game, game lasting

	static cGame* getInstance(); //Independant

private:

	static cGame* pInstance;
	// for framerates
	time_point< high_resolution_clock > m_lastTime;
	time_point< high_resolution_clock > m_CurrentTime;
	duration< double > deltaTime;
	bool loop;

	//Background,ship and alien sprites 
	cSprite spriteBackground; //BackGround
	cSprite spriteBackgroundGame;
	cSprite spriteBackgroundLoose;
	cSprite spriteBackgroundWon;
	cShip theShip; //Players Ship
	cAliens theAlien; //Space Invader Alien
	cBullet theBullet; //The Bullet

	// Fonts to use
	vector<LPCSTR> fontList; //The list of fonts
	vector<LPCSTR> fontsToUse; //Fonts to use

	// Text for Game
	vector<LPCSTR> gameTextNames; //Names of text messages (hello_txt)
	vector<LPCSTR> gameTextList; //List of texts

	// Game Sounds
	vector<LPCSTR> soundList; //Music/Sound that will be used
	vector<soundType> soundTypes; //Sound types
	vector<LPCSTR> soundsToUse; //Sounds that are going to be used

	// Game Vitiasl
	vector<LPCSTR> textName; //Textname
	vector<LPCSTR> textureName; //Texture name
	vector<LPCSTR> texturesToUse; //Textures that im using
	vector<cAliens*> theAliens; //The aliens
	vector<cBullet*> theBullets; //The bullets

	// Create vector array of button textures
	vector<LPCSTR> btnNameList; //Button name list(btn_exit) etc..
	vector<LPCSTR> btnTexturesToUse; //Button textures
	vector<SDL_Point> btnPos; //Button positions
	vector <cButton> theButtons; //The buttons

	// Game objects

	// Define the elements and there position in/on the array/map
	cTileMap theTileMap;
	int renderWidth, renderHeight; //The widt and height 
	SDL_Point theAreaClicked; //Coordinates of mouse click
	gameState theGameState; //What state the game is in: menu, play etc..
	btnTypes theBtnType; //Button types
	SDL_Rect aRect; //Rectangle
	SDL_Color aColour; //Colour
	cTexture* tempTextTexture; //A temporary texture
	SDL_Rect pos; //Positiob
	FPoint scale; //Scale
	cFileHandler theFile; //File
	bool fileAvailable; //Boolean to see if file is there true/false
	string prevScore;
};

#endif