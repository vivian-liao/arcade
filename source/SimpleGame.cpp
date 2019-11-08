// SimpleGame.cpp

#include "SimpleGame.h"

Action SimpleGame::update (SDL_Event* event)
{
    // first check if it is a new game
    if (getIsNewGame())
	{
		newGame();
	}

    // create a default action to return
	Action newAction = { DO_NOTHING, nullptr };

    //update all the entities given by passing the event
	for (int i = 0; i < getMovingEntities()->size(); i++)
	{
		(*getMovingEntities())[i]->update(event);
	}

    // execute the game logic
	logic();

    // if the gameState is false end the game
	if (getgameState() == false)
	{
		setisNewGame(true);
		setGameState(true);
		getBall()->setXVelocity(0);
		getBall()->setYVelocity(0);

		newAction = { MOVE_SCREENS, getGameOverScreen() };
		return newAction;
	}
    if(event)
    {
        if ((*event).key.keysym.sym == SDLK_q)
        {
            setisNewGame(true);
            newAction = { MOVE_NODES, getParentNode() };
            return newAction;
        }
        else if ((*event).key.keysym.sym == SDLK_p)
        {
            newAction = { MOVE_SCREENS, getPauseScreen() };
            return newAction;
        }
        else if (event && (*event).key.keysym.sym == SDLK_n)
        {
            setGameState(true);
            setisNewGame(true);
        }
    }
	
	return newAction;
}

void SimpleGame::newGame()
{
	setGameState(true);
	ball->setXPos(0);
	ball->setYPos(0);
	ball->setXVelocity(2);
	ball->setYVelocity(5);
	paddle->setXPos(0);
	paddle->setYPos(windowHeight - paddle->getHeight());
	paddle->setXVelocity(0);
	setisNewGame(false);
}

void SimpleGame::logic()
{
    if (getBall()->getXPos() < 0)
	{
		getBall()->setXPos(0);
		getBall()->setXVelocity(-(getBall()->getXVelocity()));
	}

    else if (getBall()->getYPos() < 0)
	{
		getBall()->setYPos(0);
		getBall()->setYVelocity(-(getBall()->getYVelocity()));
	}

    else if (getBall()->getXPos() + ball->getWidth() > windowWidth)
	{
		getBall()->setXPos(windowWidth - ball->getWidth());
		getBall()->setXVelocity(-(getBall()->getXVelocity()));
	}

    else if (getBall()->getYPos() + ball->getHeight() > windowHeight)
	{
		getBall()->setYPos(windowHeight - ball->getHeight());
		getBall()->setYVelocity(-(getBall()->getYVelocity()));
		//setGameState(false);
	}

	//---------------------------------------

	SDL_Rect ballRegion = getBall()->getGameObjectTexture()->getImageDestination();
	SDL_Rect paddleRegion = getPaddle()->getGameObjectTexture()->getImageDestination();

	if(SDL_HasIntersection(&ballRegion, &paddleRegion))
	{
		getBall()->setYPos(windowHeight - getBall()->getHeight() - getPaddle()->getHeight());
		getBall()->setYVelocity(-(getBall()->getYVelocity()));

		int ratio = (getBall()->getXPos() + getBall()->getWidth() / 2) - (getPaddle()->getXPos() + getPaddle()->getWidth() / 2);

		ball->setXVelocity(ratio / 4);
	}

	if(paddle->getXPos() < 0)
	{
		paddle->setXPos(0);
	}

	if(paddle->getXPos() + paddle->getWidth() > windowWidth)
	{
		paddle->setXPos(windowWidth - paddle->getWidth());
	}
}