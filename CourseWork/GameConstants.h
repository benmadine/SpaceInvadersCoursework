//cSDL2WNDManager.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _GAMECONSTANTS_H //Includes the code between this and the "#endif"
#define _GAMECONSTANTS_H

// Windows & SDL 
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <SDL.h>
// Image Texture loading library
#include <SDL_image.h>
// Font loading library
#include <SDL_ttf.h>
// Audio loading library
#include <SDL_mixer.h>
// Maths functions
#include <math.h>
#define PI 3.14159265

// File handling
#include <fstream>
#include <sstream>

// STL Container & Algorithms
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std::chrono;

using namespace std;

//Window Properties
#define WINDOW_TITLE "Spaaace Invaaaaders" //Title of window
#define WINDOW_WIDTH 1024 //Width of window
#define WINDOW_HEIGHT 768 //Height of window

// Constants & enumarated types for the game
typedef struct
{
	float  X; //Float ". number" value for x
	float  Y; //Float ". number" value for y
}FPoint;

//Types
enum textType { SOLID, BLENDED, SHADED }; //Text types
enum soundType { SFX, MUSIC }; //Sound types
enum gameState { MENU, PLAYING, END, QUIT, LOADMAP, SAVEMAP, WON, LOST }; //Game States {member}
enum btnTypes { EXIT, INSTRUCT, LOAD, PLAY, SAVE, SETTINGS }; //Button Types

#endif