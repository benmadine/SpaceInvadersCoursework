//cFileHandler.h =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Starts
#ifndef _CFILEHANDLER_H//Includes the code between this and the "#endif"
#define _CFILEHANDLER_H

#include "GameConstants.h"  //Takes from the GameConstants header file
#include <fstream>  //Input output stream so can use files

class cFileHandler
{
private:
	string m_filename; //stirng variable called file name
	fstream theFile; //file called theFile

public:
	cFileHandler(); //fileHandler
	cFileHandler(string fileName); //Cna contain the filename string

	int openFile(int mode); //Integar 
	void closeFile(); //Close file method
	string readDataFromFile(); //String to read the file
	void writeDataToFile(string textLine); //Methods to load the file
	void setFileName(string aFilename); //Method to set file name
	string getFileName(); //String getFileName
};

#endif
