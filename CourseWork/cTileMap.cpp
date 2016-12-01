/*
=================
- cTileMap.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cTileMap.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cTileMap::cTileMap() : cSprite()
{
	this->initialiseMap();
}

cTileMap::cTileMap(cFileHandler* aFile) : cSprite()
{
	this->initialiseMapFromFile(aFile);
}

void cTileMap::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, cTextureManager* theTxtMgr, vector<LPCSTR> theTxt)
{
	
}
void cTileMap::renderGridLines(SDL_Renderer* theRenderer, SDL_Rect theRect, SDL_Color theColour)
{

}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cTileMap::update(SDL_Point theMapAreaClicked, int theTileToPlace)
{
	SDL_Point areaClicked = theMapAreaClicked;
	if (theTileToPlace > -1)
	{
		if (areaClicked.x > this->mapStartXY.x && areaClicked.x < 612 && areaClicked.y > this->mapStartXY.y && areaClicked.y < 612)
		{
			this->tileClickedRC.x = (int)(areaClicked.x - this->mapStartXY.x) / this->aTile.getSpriteDimensions().w;
			this->tileClickedRC.y = (int)(areaClicked.y - this->mapStartXY.y) / this->aTile.getSpriteDimensions().h;
			this->tileMap[this->tileClickedRC.y][this->tileClickedRC.x] = theTileToPlace;
		}
	}
}
/*
=================================================================
- Set the initial values for the map
=================================================================
*/
void cTileMap::initialiseMap()
{

}
/*
=================================================================
- Set the initial values for the map from file input
=================================================================
*/
void cTileMap::initialiseMapFromFile(cFileHandler* aFile)
{
	string fileData;
	fileData = aFile->readDataFromFile();

	stringstream mapData(fileData);
	aFile->closeFile(); //Closes the file
}
/*
=================================================================
- set start position for tile map
=================================================================
*/
void cTileMap::setMapStartXY(SDL_Point startPosXY)
{
	mapStartXY = startPosXY;
}
/*
=================================================================
- get start pposition for tile map
=================================================================
*/
SDL_Point cTileMap::getMapStartXY()
{
	return mapStartXY;
}
/*
=================================================================
- get the tile map as a string
=================================================================
*/
string cTileMap::getMapData()
{
	string mapData = "";
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			mapData += to_string(this->tileMap[row][column]) + ',';
		}
		mapData += '\n';
	}
	return mapData;
}

/*
=================================================================
- Write the values from the map to the file
=================================================================
*/
void cTileMap::writeMapDataToFile(cFileHandler* aFile)
{
	string mapDataToWrite = "";
	string theMapData = this->getMapData();
	stringstream outputStr(theMapData);
	if (!theMapData.empty())
	{
		while (getline(outputStr, mapDataToWrite, '\n')){
			mapDataToWrite += '\n';
			aFile->writeDataToFile(mapDataToWrite);
		}
	}
	aFile->closeFile();
}