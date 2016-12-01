//cSoundMgr.cpp =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Includes
#include "cSoundMgr.h" //Takes from the cSoundMgr header file

cSoundMgr* cSoundMgr::pInstance = NULL; //Makes pInstance undefined 

//Constructor
cSoundMgr::cSoundMgr()
{

}

//Singleton Desgign Pattern
cSoundMgr* cSoundMgr::getInstance()
{
	if (pInstance == NULL) //If pInstance is equal to NULL
	{
		pInstance = new cSoundMgr(); //Makes pInstance equal to new cSoundMgr()
	}
	return cSoundMgr::pInstance; ////Returns pInstance
}

void cSoundMgr::add(LPCSTR sndName, LPCSTR fileName, soundType sndType)
{
	if (!getSnd(sndName)) //If get sound name
	{
		cSound * newSnd = new cSound(sndType); //NewSnd makes equal to new cSound
		newSnd->load(fileName); //newSnd loads the filename for the sound
		gameSnds.insert(make_pair(sndName, newSnd)); //Inserts the game soun
	}
}

cSound* cSoundMgr::getSnd(LPCSTR sndName)
{
	map<LPCSTR, cSound*>::iterator snd = gameSnds.find(sndName);
	if (snd != gameSnds.end()) //If souns does not equal game sound
	{
		return snd->second; //Returns sounds
	}
	else
	{
		return NULL; //Returns a false value
	}
}

void cSoundMgr::deleteSnd()
{
	for (map<LPCSTR, cSound*>::iterator snd = gameSnds.begin(); snd != gameSnds.end(); ++snd) //For snd is eqal to gameSnds -begin, snd is not equal to gameSnd - end, add 1 to snd
	{
		delete snd->second; //Delete sounds
	}
}

bool cSoundMgr::initMixer()
{
	if (SDL_Init(SDL_INIT_AUDIO) != 0) //If SDL_Init does not equal 0
	{
		cout << "SDL_Init_AUDIO Failed: " << SDL_GetError() << endl; //Displays message and ends the line
		return false; //Return false
	}
	//Initialise SDL_mixer 
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
	{
		cout << "Mix_OpenAudio Failed: " << SDL_GetError() << endl; //Displays message and ends the line
		return false; //Return flase
	}

	return true; //Return true value
}

cSoundMgr::~cSoundMgr()
{
	deleteSnd(); //Delete sound
	Mix_CloseAudio(); //Close audio
	Mix_Quit(); //Quit
}
