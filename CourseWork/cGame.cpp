/*save score*/

//cGame.cpp =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Includes
#include "cGame.h" //Takes from the cGame header file

cGame* cGame::pInstance = NULL; //Makes pInstance undefined 
static cTextureManager* theTextureManager = cTextureManager::getInstance(); 
static cFontMgr* theFontMgr = cFontMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
static cButtonMgr* theButtonMgr = cButtonMgr::getInstance();
int score = 0; //Integar varaible score = 0
string strScore; //String variable strScore


//Constructor
cGame::cGame()
{

}

//Singleton Design Pattern
cGame* cGame::getInstance()
{
	if (pInstance == NULL) //If pInstance is equal to NULL
	{
		pInstance = new cGame(); //Makes pInstance equal to new cGame()
	}
	return cGame::pInstance; //Returns pInstance
}

void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	bool easterEgg = false; //Sets the easter egg value to true
	//Backgorund dimesnions(width and height) and sets it to black
	SDL_GetRendererOutputSize(theRenderer, &renderWidth, &renderHeight);
	this->m_lastTime = high_resolution_clock::now();
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);

	theTextureManager->setRenderer(theRenderer); //Texture Manager
	theFontMgr->initFontLib(); //Font Manager
	theSoundMgr->initMixer(); //Sound Manager
	theAreaClicked = { 0, 0 }; //Sets the are clicked to (0,0) - (x,y)
	
	// Set filename
	theFile.setFileName("Data/usermap.dat"); //Filename
	// Check file is available
	if (!theFile.openFile(ios::in)) //open file for input output
	{
		cout << "Could not open specified file '" << theFile.getFileName() << "'. Error " << SDL_GetError() << endl; //Displays error message
		fileAvailable = false; //Sets boolean fileAvailable to false
	}
	else //Else
	{
		cout << "File '" << theFile.getFileName() << "' opened for input!" << endl; //Displays message that file has been found
		fileAvailable = true; //Sets boolean fileAvailable to true
	}

	//Arry of textures
	theTextureManager->setRenderer(theRenderer); //Texture Manager
	textureName = { "alien", "ship", "bullet", "background", "EasterEggBullet", "EasterEggShip", "EasterEggAlien" }; //Array of texture names
	texturesToUse = { "Images\\Alien.png", "Images\\SpaceInvader.png", "Images\\Bullet.png", "Images\\Background.jpg", "Images\\mountainJew.png", "Images\\easterEggShip.png", "Images\\easterEggAlien.png" }; //Texture file locations

	//Stores the textures in the array
	for (int tCount = 0; tCount < textureName.size(); tCount++) //For integar tcount equals 0, tcount is less than the texture size, add 1 to tcount
	{
		theTextureManager->addTexture(textureName[tCount], texturesToUse[tCount]); // Assigns textures
	}

	// Store the Buttons
	btnNameList = { "exit_btn", "instructions_btn", "load_btn", "menu_btn", "play_btn", "save_btn", "settings_btn" }; //Array of button name list
	btnTexturesToUse = { "Images/Buttons/button_exit.png", "Images/Buttons/button_instructions.png", "Images/Buttons/button_load.png", "Images/Buttons/button_menu.png", "Images/Buttons/button_play.png", "Images/Buttons/button_save.png", "Images/Buttons/button_settings.png" }; //Button texture file locations
	btnPos = { { 350, 375 }, { 350, 300 }, { 400, 300 }, { 325, 500 }, { 400, 300 }, { 740, 500 }, { 400, 300 } }; //Position of the buttons
	for (int bCount = 0; bCount < btnNameList.size(); bCount++) //For integar bcount equals 0, bcount is less than the button name list, add 1 to bcount
	{
		theTextureManager->addTexture(btnNameList[bCount], btnTexturesToUse[bCount]); //Adds the button texture to use
		cButton * newBtn = new cButton(); //newBtn equals to new cButton()
		newBtn->setTexture(theTextureManager->getTexture(btnNameList[bCount])); //Sets texture for the button
		newBtn->setSpritePos(btnPos[bCount]); //Sets button position
		newBtn->setSpriteDimensions(theTextureManager->getTexture(btnNameList[bCount])->getTWidth(), theTextureManager->getTexture(btnNameList[bCount])->getTHeight()); //Sets button dimensions
		theButtonMgr->add(btnNameList[bCount], newBtn); //Adds button
	}

	theGameState = MENU; //Sets current game state to Menu
	theBtnType = EXIT; //Sets button type to exit

	//Create texture for text and write texts
	fontList = { "digital", "spaceAge" }; //Array of font names
	fontsToUse = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" }; //Font type file locations
	for (int fonts = 0; fonts < fontList.size(); fonts++) //For, integar font = to, fonts to be less than font list size, add 1 to fonts
	{
		theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 48); //Adds the font
	}
	gameTextNames = { "TitleTxt", "CreateTxt", "ThanksTxt", "SeeYouTxt", "ScoreTxt", "ContorlsTxt", "WONTxt", "ContorlsTxt2", "LostTxt"}; //The name of texts in the game
	gameTextList = { "Space Invaders", "Survive the Aliens", "Thanks for playing!", "Game Over!", "Score: ", "Use the arrow keys to move", "YOU WON!!", "and the space bar to shoot", "You lost:((((("}; //The messages in the text
	for (int text = 0; text < gameTextNames.size(); text++) //For, integar text = 0, text is less than text name size, add 1 to text
	{
		theTextureManager->addTexture(gameTextNames[text], theFontMgr->getFont("digital")->createTextTexture(theRenderer, gameTextList[text], SOLID, { 228, 213, 238, 255 }, { 0, 0, 0, 0 })); //Adds the font type digital and have a solid clear background to it
	}

	//Load game sounds
	soundList = { "theme", "click" , "shot", "explosion", "Motivation"}; //Array of sound names
	soundTypes = { MUSIC, SFX, SFX, SFX, SFX}; //Sound types
	soundsToUse = { "Audio/Theme/15684__marec__neutron.wav", "Audio/SFX/343015__zenithinfinitivestudios__ui-button1.wav", "Audio/SFX/42994__noisecollector__blasters.wav", "Audio/SFX/270314__thenetherchickens__eeehhh.wav", "Audio/SFX/259681__xtrgamr__die.wav" }; //Sound file locations
	for (int sounds = 0; sounds < soundList.size(); sounds++) //Integar sounds is equal to 0, sounds is less than the sound list size, add 1 to sounds
	{
		theSoundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]); //Adds the sound to use
	}

	theSoundMgr->getSnd("theme")->play(-1); //Makes the theme play out through the whole game

	//Sets the background position, gets image and dimensions
	spriteBackground.setSpritePos({ 0, 0 }); //Background position
	spriteBackground.setTexture(theTextureManager->getTexture("background")); //Gets texure for the background
	spriteBackground.setSpriteDimensions(theTextureManager->getTexture("background")->getTWidth(), theTextureManager->getTexture("background")->getTHeight()); //Width and height of the background

	//Sets the SpaceShip position, gets imahe and dimensions
	theShip.setSpritePos({ 500, 700 }); //Ship position
	theShip.setTexture(theTextureManager->getTexture("ship")); //Gets the ship texture
	theShip.setSpriteDimensions(theTextureManager->getTexture("ship")->getTWidth(), theTextureManager->getTexture("ship")->getTHeight()); //Width and height of the ship
	theShip.setShipVelocity({ 0, 0 }); //Ships elocity

	//Aliens - Vector Array
	for (int aly = 0; aly < 4; aly++) // Change the 35 to number of desired aliens
	{
		theAliens.push_back(new cAliens);
		theAliens[aly]->setSpritePos({ 100 + (266*aly), 0}); //How do i get aliens to spawn in a row...
		theAliens[aly]->setSpriteTranslation({ -10, 0 }); //Aliens movement
		theAliens[aly]->setTexture(theTextureManager->getTexture("alien")); //Gets alien texure
		theAliens[aly]->setSpriteDimensions(theTextureManager->getTexture("alien")->getTWidth(), theTextureManager->getTexture("alien")->getTHeight()); //Aliens width and height
		theAliens[aly]->setActive(true);
	}

}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	loop = true; //Boolean loop set to true

	while (loop) //While loop
	{
		double elapsedTime = this->getElapsedSeconds(); //Time passed since last frame
		loop = this->getInput(loop); //loop equal to input
		this->update(elapsedTime); //Elapsed time
		this->render(theSDLWND, theRenderer); //Render
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer); //The renderer
	switch (theGameState) //Changes the gamestate
	{
	case MENU: //Main Menu
	{
		//Renders the background
		spriteBackground.render(theRenderer, NULL, NULL, spriteBackground.getSpriteScale());
		//Texts render is main menu screen
		tempTextTexture = theTextureManager->getTexture("TitleTxt"); //Temperory txture set to Title text
		pos = { 350, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h }; //Positon of the text
		scale = { 1, 1 }; //Scale of the text
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale); //Renders the text with the scale and position
		tempTextTexture = theTextureManager->getTexture("ContorlsTxt"); //Temporary texture set to Contorls text
		pos = { 250, 100, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h }; //Position of the texure
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale); //Renders the texture with scale and position
		tempTextTexture = theTextureManager->getTexture("ContorlsTxt2"); //Temporary texture set to Contorls text
		pos = { 250, 150, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h }; //Position of the texure
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//Renders the Buttons
		theButtonMgr->getBtn("play_btn")->render(theRenderer, &theButtonMgr->getBtn("play_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("play_btn")->getSpritePos(), theButtonMgr->getBtn("play_btn")->getSpriteScale()); //Renders the play button
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 350, 375 }); //Position of the exit button
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale()); //Renders the exit button
	}
	break;
	case PLAYING: //Play Scene
	{
		//Renders the Background
		spriteBackground.render(theRenderer, NULL, NULL, spriteBackground.getSpriteScale()); //Renders background
		//Score Text	
		theTextureManager->addTexture("ScoreTxt", theFontMgr->getFont("digital")->createTextTexture(theRenderer, strScore.c_str(), SOLID, { 228, 213, 238, 255 }, { 0, 0, 0, 0 })); //Renders score text with the font type and solid background
		tempTextTexture = theTextureManager->getTexture("ScoreTxt"); //Sets temporary texture to score text
		pos = { 300, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h }; //Position of score text
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale); //Renders score text
		//Renders the exit button
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 940, 575 }); //Exit button position
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale()); //Renders exit button
		//Renders the load button
		theButtonMgr->getBtn("load_btn")->setSpritePos({ 940, 620 }); //Load button position
		theButtonMgr->getBtn("load_btn")->render(theRenderer, &theButtonMgr->getBtn("load_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("load_btn")->getSpritePos(), theButtonMgr->getBtn("load_btn")->getSpriteScale()); //Renders load button
		//Renders the save button
		theButtonMgr->getBtn("save_btn")->setSpritePos({ 940, 695 }); //Save button position
		theButtonMgr->getBtn("save_btn")->render(theRenderer, &theButtonMgr->getBtn("save_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("save_btn")->getSpritePos(), theButtonMgr->getBtn("save_btn")->getSpriteScale()); //Renders the save button
		//Renders the Bullets
		for (int draw = 0; draw < theBullets.size(); draw++) //For integar draw equals to 0, draw is less than the bullet size, add 1 to draw
		{
			theBullets[draw]->render(theRenderer, &theBullets[draw]->getSpriteDimensions(), &theBullets[draw]->getSpritePos(), theBullets[draw]->getSpriteRotAngle(), &theBullets[draw]->getSpriteCentre(), theBullets[draw]->getSpriteScale()); //Renders the bullet with scale, gets the centre of the bullet and sprite position
		}
		//Render the Aliens
		for (int draw = 0; draw < theAliens.size(); draw++) //For integar draw equals to 0, draw is less than the alien size, add 1 to draw
		{
			theAliens[draw]->render(theRenderer, &theAliens[draw]->getSpriteDimensions(), &theAliens[draw]->getSpritePos(), theAliens[draw]->getSpriteRotAngle(), &theAliens[draw]->getSpriteCentre(), theAliens[draw]->getSpriteScale()); //Renders the alien with scale, gets the centre of the alien and alien position
		}
		//Renders the Ship
		theShip.render(theRenderer, &theShip.getSpriteDimensions(), &theShip.getSpritePos(), theShip.getSpriteRotAngle(), &theShip.getSpriteCentre(), theShip.getSpriteScale()); //Renders the ship with scale and gets the ships centre and position
	}
	break;
	case END: //End Scene
	{
		//Renders the Backgrounds
		spriteBackground.render(theRenderer, NULL, NULL, spriteBackground.getSpriteScale()); //Renders the background
		//Renders the texts
		theTextureManager->addTexture("ScoreTxt", theFontMgr->getFont("digital")->createTextTexture(theRenderer, strScore.c_str(), SOLID, { 228, 213, 238, 255 }, { 0, 0, 0, 0 })); //Renders score text with the font type and solid background
		tempTextTexture = theTextureManager->getTexture("ScoreTxt"); //Sets temporary texture to score text
		pos = { 400, 100, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h }; //Position of score text
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale); //Renders score text
		tempTextTexture = theTextureManager->getTexture("ThanksTxt"); //Temporary texture set to thanks text
		pos = { 400, 200, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h }; //Position of text
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale); //Renders the text
		tempTextTexture = theTextureManager->getTexture("SeeYouTxt"); //Temporary texture set to seeyou text
		pos = { 400, 300, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h }; //Position of text
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale); //Renders the text
		//Renders the Buttons
		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 500, 500 }); //Menu button position
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale()); //Renders menu button
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 500, 575 }); //Exit Button position
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale()); //Renders exit button
	}
	break;
		case LOST:
		{
			//Renders the Backgrounds
			spriteBackground.render(theRenderer, NULL, NULL, spriteBackground.getSpriteScale()); //Renders the background
			//Renders the texts
			theTextureManager->addTexture("ScoreTxt", theFontMgr->getFont("digital")->createTextTexture(theRenderer, strScore.c_str(), SOLID, { 228, 213, 238, 255 }, { 0, 0, 0, 0 })); //Renders score text with the font type and solid background
			tempTextTexture = theTextureManager->getTexture("ScoreTxt"); //Sets temporary texture to score text
			pos = { 400, 100, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h }; //Position of score text
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale); //Renders score text
			tempTextTexture = theTextureManager->getTexture("LostTxt"); //Temporary texture set to thanks text
			pos = { 400, 200, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h }; //Position of text
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale); //Renders the text
			tempTextTexture = theTextureManager->getTexture("SeeYouTxt"); //Temporary texture set to seeyou text
			pos = { 400, 300, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h }; //Position of text
			tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale); //Renders the text
			//Renders the Buttons
			theButtonMgr->getBtn("menu_btn")->setSpritePos({ 500, 500 }); //Menu button position
			theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale()); //Renders menu button
			theButtonMgr->getBtn("exit_btn")->setSpritePos({ 500, 575 }); //Exit Button position
			theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale()); //Renders exit button
		}
	break;	
	case WON: //Win Scene
	{
		//Renders the Backgrounds
		spriteBackground.render(theRenderer, NULL, NULL, spriteBackground.getSpriteScale()); //Renders the background
		//Renders the texts
		theTextureManager->addTexture("ScoreTxt", theFontMgr->getFont("digital")->createTextTexture(theRenderer, strScore.c_str(), SOLID, { 228, 213, 238, 255 }, { 0, 0, 0, 0 })); //Renders score text with the font type and solid background
		tempTextTexture = theTextureManager->getTexture("ScoreTxt"); //Sets temporary texture to score text
		pos = { 400, 100, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h }; //Position of score text
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale); //Renders score text
		tempTextTexture = theTextureManager->getTexture("WONTxt"); //Temporary texture set to thanks text
		pos = { 400, 200, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h }; //Position of text
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale); //Renders the text
		tempTextTexture = theTextureManager->getTexture("ThanksTxt"); //Temporary texture set to seeyou text
		pos = { 400, 300, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h }; //Position of text
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale); //Renders the text
		//Renders the Buttons
		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 500, 500 }); //Menu button position
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale()); //Renders menu button
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 500, 575 }); //Exit Button position
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale()); //Renders exit button
	}
	break;
	case QUIT: //Quit Scene
	{
		//Changed this to bool loop so it worked, check if its right later......
		loop = false;
	}
	break;
	default:
		break;
	}
	SDL_RenderPresent(theRenderer); 
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{

	SDL_RenderPresent(theRenderer); 
}

void cGame::update()
{

}

void cGame::update(double deltaTime)
{
	// CHeck Button clicked and change state
	switch (theGameState) //Switch game state
	{
	case MENU: //Menu Scene
	{
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked); //Clicking exit button changes the game state to quit
		theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, PLAYING, theAreaClicked); //Click play button changes the game state to playing
	}
	break;
	case PLAYING: //Playing scene
	{
		if (score == 400) //If players score is equal to 400
		{
			cout << "Trying to get to won pls" << endl;
			theGameState = WON;
		}
		for (int alyBob = 0; alyBob < 1; alyBob++/*int alyBob = 0; alyBob < theAliens.size; alyBob++*/) // Change the 35 to number of desired aliens
		{
			if (theAliens[alyBob]->getSpritePos().y >= 500)
			{
				cout << "Trying to get to loss pls" << endl;
				theGameState = LOST;
			}
		}
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, END, theAreaClicked); //Clicking exit button changes the game to state to quit
		theGameState = theButtonMgr->getBtn("load_btn")->update(theGameState, LOADMAP, theAreaClicked); //Clicking the load button will change the game state to load
		if (fileAvailable && theGameState == LOADMAP) //If the file is avaiable and the game state is in load
		{
			cout << "Loading..." << endl;
			theTileMap.initialiseMapFromFile(&theFile); //Takes the file from the file location
			theGameState = PLAYING; //Makes game state to Play
			theAreaClicked = { 0, 0 }; //Sets are clicked to (0,0) - (x,y)
		}
		theGameState = theButtonMgr->getBtn("save_btn")->update(theGameState, SAVEMAP, theAreaClicked); //If save button is clicked changes the game state to savemap
		if (theGameState == SAVEMAP) //If the game state is Savemap
		{
			// Check file is available
			if (!theFile.openFile(ios::out)) //open file for output
			{
				cout << "Could not open specified file '" << theFile.getFileName() << "'. Error " << SDL_GetError() << endl; //Displays error messgae if file isnt avaiable and ends the line
			}
			else //Else
			{
				//Shows player that the game has been saved with a message box
				int msgboxID = MessageBox( //Message box
					NULL,
					"Saved The File", //Text inside the message box
					"File Management", //Title of the message box
					MB_ICONASTERISK | MB_OK
					);
				cout << "File '" << theFile.getFileName() << "' opened for output!" << endl; // Displays a message and ends the line
				theTileMap.writeMapDataToFile(&theFile); //Saves the file
			}
			theTileMap.writeMapDataToFile(&theFile); // Saves the file
			theGameState = PLAYING; //Sets game state to playing
			theAreaClicked = { 0, 0 }; //Sets are clicked to (0,0) - (x,y)
		}
		//visibility and position of each alien
		vector<cAliens*>::iterator alienIterator = theAliens.begin(); //AlienIterator equal the aliens
		while (alienIterator != theAliens.end()) //While alienIterator does not equal the aliens
		{
			if ((*alienIterator)->isActive() == false) //If set active is equal to false
			{
				alienIterator = theAliens.erase(alienIterator); //alien Iterator equals the aliens, erase the aliens
			}
			else //Else
			{
				(*alienIterator)->update(deltaTime);
				++alienIterator; //Add 1 to alienIterator
			}
		}
		//visibility and position of each bullet
		vector<cBullet*>::iterator bulletIterartor = theBullets.begin(); //BulletIterator is equal to bullets and it begins
		while (bulletIterartor != theBullets.end()) //While the bullet iterator does not equal the bullets - end it
		{
			if ((*bulletIterartor)->isActive() == false) //If set active is equal to false
			{
				bulletIterartor = theBullets.erase(bulletIterartor); //Bullet Iterator equals the bullet, erase the bullets
			}
			else //Else
			{
				(*bulletIterartor)->update(deltaTime);
				++bulletIterartor; //Add one to bulletIterator
			}
		}
		//Check for collisions
		for (vector<cBullet*>::iterator bulletIterartor = theBullets.begin(); bulletIterartor != theBullets.end(); ++bulletIterartor) //For Bullets to start
		{
			//(*bulletIterartor)->update(deltaTime);
			for (vector<cAliens*>::iterator alienIterator = theAliens.begin(); alienIterator != theAliens.end(); ++alienIterator) //For aliens to start
			{
				if ((*alienIterator)->collidedWith(&(*alienIterator)->getBoundingRect(), &(*bulletIterartor)->getBoundingRect())) //If bullet colides with alien
				{
					//If a collision set the bullet and alien to false
					(*alienIterator)->setActive(false);
					(*bulletIterartor)->setActive(false);
					theSoundMgr->getSnd("explosion")->play(0); //Plays the sound explosion
					score += 100; //Adds 100 to player score
					strScore = gameTextList[4] + to_string(score); //Updates the score text
					theTextureManager->deleteTexture("ScoreTxt");
					cout << "Player's score is: " << score << endl; //Player score is console
				}
			}
		}
		theShip.update(deltaTime); //Update the Rockets position
	}
	break;
	case END: //End scene
	{
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked); //If exit button clicked then change game state to quit
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, MENU, theAreaClicked); //If menu button clicked the change game state to menu
	}
	break;
	case QUIT:
	{
	}
	break;
	//Player loosing or winning the game
	case LOST:
	{
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked); //If exit button clicked then change game state to quit
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, MENU, theAreaClicked); //If menu button clicked the change game state to menu
	}
	break;
	case WON:
	{
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked); //If exit button clicked then change game state to quit
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, MENU, theAreaClicked); //If menu button clicked the change game state to menu
	}
	break;
	default:
		break;
	}
}

bool cGame::getInput(bool theLoop)
{
	SDL_Event event; //Makes an event

	while (SDL_PollEvent(&event)) //While the 
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false; //Makes the loop boolean equal to false
		}

		//Movement keys
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN: //Mouse button down
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT: //Mouse button left click
			{
				theSoundMgr->getSnd("click")->play(0);
				theAreaClicked = { event.motion.x, event.motion.y }; //The area clicked, coordinates of clicks
			}
			break;
			case SDL_BUTTON_RIGHT: //Mouse button right click
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP: //Mouse button up
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT: //Mouse button, left click
			{
				if (theGameState == PLAYING) //If gamestate is in Playing
				{
					theSoundMgr->getSnd("click")->play(0);
					theAreaClicked = { event.motion.x, event.motion.y }; //The area clicked, cooridantes of click
				}
			}
			break;
			case SDL_BUTTON_RIGHT: //Mouse button, right click
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			break;
		case SDL_KEYDOWN: //Keys
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE: //Escape key
				theLoop = false; //Loop boolean is set to false
				break; //Breaks the program

			case SDLK_RIGHT: //Right arrow key
			{
				if (theShip.getSpritePos().x < 850) //If ships position is less than 850
				{
					theShip.setShipVelocity({ 25, 0 }); //Ships velocity is set to 25, so moves right
				}
			}
			break;
			case SDLK_w:
			{
				theSoundMgr->getSnd("Motivation")->play(0);
				cout << "You discovered the easter egg of motivation woooo";
			}
			break;
			case SDLK_i:
			{
				bool easterEgg = true;
				cout << "You have activated the easter egg";
			}
			break;
			case SDLK_LEFT: //Left arrow key
			{
				if (theShip.getSpritePos().x > 0) //If ships position is greator than 0
				{
					theShip.setShipVelocity({ -25, 0 }); // Ships velocity is set to -25, so moves left
				}
			}
			break;
			case SDLK_SPACE: //Space bar key
			{
				theBullets.push_back(new cBullet); 
				int numBullets = theBullets.size() - 1; //Decreases the number of bullets by 1
				theBullets[numBullets]->setSpritePos({ theShip.getBoundingRect().x + theShip.getSpriteCentre().x, theShip.getBoundingRect().y + theShip.getSpriteCentre().y }); //Spawns the bullets in the centre of the ship
				theBullets[numBullets]->setSpriteTranslation({ 2.0f, 2.0f }); //Sets bullet translation
				theBullets[numBullets]->setTexture(theTextureManager->getTexture("bullet")); //Get the bullet texture
				theBullets[numBullets]->setSpriteDimensions(theTextureManager->getTexture("bullet")->getTWidth(), theTextureManager->getTexture("bullet")->getTHeight()); //Renders the bullet
				theBullets[numBullets]->setBulletVelocity({ 2.0f, 2.0f }); //Sets the bullet velocity
				theBullets[numBullets]->setSpriteRotAngle(theShip.getSpriteRotAngle()); //Set the rotation angle for the bullet
				theBullets[numBullets]->setActive(true); //Sets theBullets to active
				cout << "Bullet added to Vector at position - x: " << theShip.getBoundingRect().x << " y: " << theShip.getBoundingRect().y << endl; //Displays a message and ends the line
			}
			theSoundMgr->getSnd("shot")->play(0); //Plays a sound when the bullet is fired
			break;
			default:
				break;
			}

		default:
			break;
		}

	}
	return theLoop; //Returns the loop
}

double cGame::getElapsedSeconds()
{
	//The time in the game
	this->m_CurrentTime = high_resolution_clock::now(); 
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
	//Time in the game
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}