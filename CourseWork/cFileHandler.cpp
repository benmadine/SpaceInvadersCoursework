//cFileHandler.cpp =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Includes
#include "cFileHandler.h" //Takes from the cFileHandler header file

//Default Constructor
cFileHandler::cFileHandler()
{
	m_filename = ""; //Sets filename name
}
cFileHandler::cFileHandler(string fileName)
{
	m_filename = fileName; //Makes m_filename equal fileName
}

int cFileHandler::openFile(int mode)
{
	theFile.open(m_filename, mode); //The file is open
	if (!theFile.is_open())  //Cant open file
	{
		return ERROR; //Returns an error
	}
	else //Else
	{
		return TRUE; //Return true, everything is working properly
	}
}

void cFileHandler::closeFile()
{
	theFile.close(); //Close the file
}

string cFileHandler::readDataFromFile()
{
	string lineFromFile; //Makes a string variable, lineFromFile
	string output; //Makes a string variable, output
	while (getline(theFile, lineFromFile)) //While getline
	{
		output += lineFromFile;  // Output is equal and adds to the lineFromFile
	}
	return output; //Returns output
}

void cFileHandler::writeDataToFile(string textLine)
{
	theFile << textLine; //The file 
}

//Sets the file name
void cFileHandler::setFileName(string aFilename)
{
	this->m_filename = aFilename; //Sets the file name
}

//Gets the file name
string cFileHandler::getFileName()
{
	return this->m_filename; //Returns the file name
}