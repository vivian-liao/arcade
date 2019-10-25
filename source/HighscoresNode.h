// HighscoresNode.h

#include "Node.h"
#include "MenuScreen.h"
#include "SimpleButton.h"
#include "Config.h"

class HighscoresNode : public Node
{
// all the variables this Node will hold
private:
	Node* parentNode;
public:
	// pass this in from main when you create it
	HighscoresNode(SDL_Renderer* renderer_in = nullptr, Node* parentNode_in = nullptr) :
		Node(renderer_in, parentNode_in), parentNode(parentNode_in)
	{
		MenuScreen* highscoresScreen = createMenuScreen();

		ArcadeTexture* highscoresNodeScreenBackground = createImage(renderer_in, "highscoresNodeImages/highscoresNodeScreenBackground.png", true);
		highscoresScreen->addTextureToScreen(highscoresNodeScreenBackground);

		ArcadeTexture* highscoresText = createSimpleText(renderer_in, "fonts/retro/italic.ttf",100, "HIGHSCORES", 255, 255, 0);
		highscoresText->setPosition(windowWidth / 2 - highscoresText->getW() / 2, 20);
		highscoresScreen->addTextureToScreen(highscoresText);
		
		SimpleButton* mainMenuButton = createSimpleTextButton(renderer_in, "fonts/pixel/classic.ttf", 30, "MAIN MENU",255, 0, 0);
		mainMenuButton->setButtonPosition(windowWidth / 2 - mainMenuButton->getWidth() / 2, windowHeight - 50);
		mainMenuButton->setButtonAction(createAction(MOVE_NODES, parentNode));
		highscoresScreen->addButtonToScreen(mainMenuButton);

		this->addScreen(highscoresScreen);
		this->setCurrentScreen(highscoresScreen);
		//-------------------------------------------------------------------------------------------------------
	}
};