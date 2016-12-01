//cSound.cpp =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//#pragma warning ( disable : 4996 )
#include "cSound.h"
using namespace std;

cSound::cSound()
{
	this->theSoundType = SFX; //SFX sound type
}
cSound::cSound(soundType sndType)
{
	this->theSoundType = sndType; //Makes the sound type eqal sndType
}

cSound::~cSound()
{
}

bool cSound::load(LPCSTR filename)
{
	switch (this->theSoundType) //Changes the sound type
	{
		case SFX: //For SFX sound type
		{
			this->SoundFX = Mix_LoadWAV(filename); //Makes soundFX equal the sound file going to be used
			if (this->SoundFX == NULL) //If SoundFX is undefined
			{
				cout << "Sound FX '" << filename << "' could not be loaded. " << SDL_GetError() << endl; //Display message that the sound can not be loaded and end line 
				return false; //Retrun false value
			}
			cout << "Sound FX '" << filename << "' loaded successfully!. " << endl; //Display message that file can be loaded and end the line
			return true; //Return true value
		}
		break;
		case MUSIC: //For Music sound type
		{
			this->sMusic = Mix_LoadMUS(filename); //Makes sMusic equal to the music file going to be used
			if (this->sMusic == NULL) //If sMusic is undefined
			{
				cout << "Music '" << filename << "' could not be loaded. " << SDL_GetError() << endl; //Displays message that music could not be loaded and ends the line
				return false; //Return false value
			}
			cout << "Music '" << filename << "' loaded successfully!. " << endl; //Displays message that music has been succesfully loaded and end the line
			return true; //Return true value
		}
		break;
		default:
			return false; //Return false value
	}
}

void cSound::play(int loop)
{
	switch (this->theSoundType)
	{
		case SFX: //For SFX
		{
			Mix_PlayChannel(-1, this->SoundFX, loop); //Plays the music
		}
		break;
		case MUSIC: //For Music
		{
			Mix_PlayMusic(this->sMusic, loop); //Plays the music
		}
		break;
		default:
			break;
	}
}
