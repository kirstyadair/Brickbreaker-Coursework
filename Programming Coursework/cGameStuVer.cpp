/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();

/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{

}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}


void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);

	this->m_lastTime = high_resolution_clock::now();

	theTextureMgr->setRenderer(theRenderer);
	theTextureMgr->addTexture("theBackground", "Images\\background.png");
	
	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());

	theTextureMgr->addTexture("thePaddle", "Images\\tile.png");
	paddleSprite.setSpritePos({ (375-((theTextureMgr->getTexture("thePaddle")->getTWidth())/2)), 450 });
	paddleSprite.setTexture(theTextureMgr->getTexture("thePaddle"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("thePaddle")->getTWidth(), theTextureMgr->getTexture("thePaddle")->getTHeight());

	int xPos = 40;
	int yPos = 20;
	
	theTextureMgr->addTexture("theRedBlock", "Images\\Red.png");
	theTextureMgr->addTexture("theOrangeBlock", "Images\\Orange.png");
	theTextureMgr->addTexture("theYellowBlock", "Images\\Yellow.png");
	theTextureMgr->addTexture("theGreenBlock", "Images\\Green.png");
	theTextureMgr->addTexture("theBlueBlock", "Images\\Blue.png");
	theTextureMgr->addTexture("theDarkBlueBlock", "Images\\BlueAGAIN.png");
	theTextureMgr->addTexture("thePurpleBlock", "Images\\Purple.png");
	theTextureMgr->addTexture("thePinkBlock", "Images\\Pink.png");
	theTextureMgr->addTexture("theMagentaBlock", "Images\\PinkAGAIN.png");


	for (int i = 0; i < 16; i++) 
	{
		for (int j = 0; j < 9; j++)
		{
			blocks[i][j].setSpritePos({ (i * xPos)+55,(j*yPos)+55 });
			numberOfBlocks++;

			switch (j) 
			{
				case 0:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theRedBlock"));
				}
				break;
				case 1:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theOrangeBlock"));
				}
				break;
				case 2:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theYellowBlock"));
				}
				break;
				case 3:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theGreenBlock"));
				}
				break;
				case 4:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theBlueBlock"));
				}
				break;
				case 5:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theDarkBlueBlock"));
				}
				break;
				case 6:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("thePurpleBlock"));
				}
				break;
				case 7:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("thePinkBlock"));
				}
				break;
				case 8:
				{
					blocks[i][j].setTexture(theTextureMgr->getTexture("theMagentaBlock"));
				}
				break;
			}
			
			
		}
		
	}
	
	theTextureMgr->addTexture("theBall", "Images\\ball.png");
	ballSprite.setSpritePos({ (375 - ((theTextureMgr->getTexture("theBall")->getTWidth()) / 2)), (450-(theTextureMgr->getTexture("theBall")->getTHeight())) });
	ballSprite.setTexture(theTextureMgr->getTexture("theBall"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBall")->getTWidth(), theTextureMgr->getTexture("theBall")->getTHeight());

	ballSprite.initialise();
	paddleSprite.initialise();

	cout << numberOfBlocks;
}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	bool loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
	paddleSprite.render(theRenderer, &paddleSprite.getSpriteDimensions(), &paddleSprite.getSpritePos(), NULL, &paddleSprite.getSpriteCentre(), paddleSprite.getSpriteScale());
	ballSprite.render(theRenderer, &ballSprite.getSpriteDimensions(), &ballSprite.getSpritePos(), NULL, &ballSprite.getSpriteCentre(), ballSprite.getSpriteScale());
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			blocks[i][j].render(theRenderer, &blocks[i][j].getSpriteDimensions(), &blocks[i][j].getSpritePos(), NULL, &blocks[i][j].getSpriteCentre(), blocks[i][j].getSpriteScale());
		}
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
	paddleSprite.update(deltaTime);
	ballSprite.update(deltaTime);
}

bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym) {

			case SDLK_LEFT:
				paddleSprite.isGoingLeft = false;
				if (!(ballSprite.isMoving))
				{
					ballSprite.isGoingLeft = false;
				}
				break;

			case SDLK_RIGHT:
				paddleSprite.isGoingRight = false;
				if (!(ballSprite.isMoving))
				{
					ballSprite.isGoingRight = false;
				}
				break;

			default:
				break;
			}
		}
			

		if (event.type == SDL_KEYDOWN)
		{
			SDL_Rect currentPos = paddleSprite.getSpritePos();

			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				theLoop = false;
				break;

			case SDLK_LEFT:
				paddleSprite.isGoingLeft = true;
				if (!(ballSprite.isMoving))
				{
					ballSprite.isGoingLeft = true;
				}
				break; 
			
			case SDLK_RIGHT:
				paddleSprite.isGoingRight = true;
				if (!(ballSprite.isMoving))
				{
					ballSprite.isGoingRight = true;
				}
				break;

			case SDLK_SPACE:
				ballSprite.isMoving = true;
				cout << ballSprite.isMoving;
				break;

			default:
				break;
			}
		}
	}
	return theLoop;
}

double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
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
