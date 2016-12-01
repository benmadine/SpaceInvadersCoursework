//cSound.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _SOUND_H //Includes the code between this and the "#endif"
#define _SOUND_H

//Includes
#include "GameConstants.h" //Takes from the GameConstants header file
#include <string> //Allows the use of strings
#include <iostream> //Allows the input output
#include <fstream> //Allows for input output of files

//Standard Libary allows to use input output
using namespace std;

class cSound
{
private:

	Mix_Chunk * SoundFX = NULL;
	Mix_Music * sMusic = NULL;
	soundType theSoundType; //The sound type

public:
	cSound();
	cSound(soundType sndType);
	~cSound();

	bool load(LPCSTR filename); //Boolean, load filename 
	void setSoundTYpe(soundType sndType); //Set sound type
	soundType getSoundType(); //Get sound type
	void play(int loop);  //Use -1 for indifinate loop 
};
#endif