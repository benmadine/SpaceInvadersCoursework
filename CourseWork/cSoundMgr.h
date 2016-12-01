//cSoundMgr.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _SOUNDMGR_H //Includes the code between this and the "#endif"
#define _SOUNDMGR_H

//Includes
#include "GameConstants.h" //Takes from the GameConstants header file
#include "cSound.h" //Takes from the sound header file

//Standard Libary allows to use input output
using namespace std;

class cSoundMgr
{
private:
	static cSoundMgr* pInstance;

protected:
	cSoundMgr();
	~cSoundMgr();
	map <LPCSTR, cSound*> gameSnds;

public:
	void add(LPCSTR sndName, LPCSTR fileName, soundType sndType); //Adds the sounds
	cSound* getSnd(LPCSTR sndName); //Get sound and sound name
	void deleteSnd(); //Delete sound
	bool initMixer(); //Boolean mixer
	static cSoundMgr* getInstance();
};
#endif