// RootNode.h

#include "Node.h"
#include "Config.h"
#include "MenuScreen.h" 
#include "SimpleButton.h" 
#include "HighscoresNode.h"
#include "GameMenuNode.h"
#include "OptionsNode.h"
 
class RootNode : public Node // inherits from Node
{
private:
 
    // every node holds pointers to its children
    HighscoresNode* highscoresNode; 
    GameMenuNode* gameMenuNode;
    OptionsNode* optionsNode;
 
    // every node holds a pointer to its parent
    Node* parentNode = nullptr;
public:
    // pass this in from main when you create it
    RootNode(SDL_Renderer* renderer_in = nullptr, Node* parentNode_in = nullptr)
        // We must do this initialization list in this way because the constructor for the highscoresNode
        // actually is called before rootNode because we made a highscoresNode object a memebr variable.
        // Also, because we inherit from Node, its constructor is called first. However, because these are 
        // parametrized constructor, this initialization list actually gets checked before the parent constructor
        // in order to determine which parent contructor to call. So what happens is:
 
        // 1. Create RootNode object 2. Go to RootNode constructor initialization list 3. Go to RootNode's Node construcor
        // 4. Go to HighscoresNode constructor initialization list 5. go to HighscoresNode's Node constructor
        // 6. Go to Highscores's constructor 7. Go to RootNode's constructor
        : Node(renderer_in, parentNode_in)
    {
        // first create the children nodes and add them to the list
        highscoresNode = new HighscoresNode(getRenderer(), this);
        gameMenuNode = new GameMenuNode(getRenderer(), this);
        optionsNode = new OptionsNode(getRenderer(), this);

        children.push_back(highscoresNode);
        children.push_back(gameMenuNode);
        children.push_back(optionsNode);
 
        // first create a MenuScreen object
        MenuScreen* rootNodeScreen = createMenuScreen();
 
        // create an image to put on the screen using an ArcadeTexture object
        ArcadeTexture* rootNodeScreenBackground = createImage(renderer_in, "rootNodeImages/rootNodeScreenBackground.png", true);
        rootNodeScreen->addTextureToScreen(rootNodeScreenBackground);
 
        // create text to put on the screen using an ArcadeTexture object, initialize its size and position
        ArcadeTexture* mainMenuText = createSimpleText(renderer_in, "fonts/retro/italic.ttf", 100, "MAIN MENU", 255, 255, 0);
        mainMenuText->setPosition(windowWidth / 2 - mainMenuText->getW() / 2, 25);
        rootNodeScreen->addTextureToScreen(mainMenuText);
 
 
        // make a text button to put on the screen
        SimpleButton* highscoresButton = createSimpleTextButton(renderer_in, "fonts/pixel/classic.ttf", 30, "HIGHSCORES", 255, 0, 0);
        highscoresButton->setButtonPosition(windowWidth / 2 - highscoresButton->getWidth() / 2,
            mainMenuText->getY() + mainMenuText->getH() + 50);
        highscoresButton->setButtonAction(createAction(MOVE_NODES, highscoresNode));
        rootNodeScreen->addButtonToScreen(highscoresButton);
 
        SimpleButton* gameMenuButton = createSimpleTextButton(renderer_in, "fonts/pixel/classic.ttf", 30, "GAME MENU", 255, 0, 0);
        gameMenuButton->setButtonPosition(windowWidth / 2 - gameMenuButton->getWidth() / 2,
            highscoresButton->getY() + highscoresButton->getHeight() + 25);
        gameMenuButton->setButtonAction(createAction(MOVE_NODES, gameMenuNode));
        rootNodeScreen->addButtonToScreen(gameMenuButton);
 
        SimpleButton* optionsButton = createSimpleTextButton(renderer_in, "fonts/pixel/classic.ttf", 30, "OPTIONS", 255, 0, 0);
        optionsButton->setButtonPosition(windowWidth / 2 - optionsButton->getWidth() / 2, 
            gameMenuButton->getY() + gameMenuButton->getHeight() + 25);
        optionsButton->setButtonAction(createAction(MOVE_NODES, optionsNode));
        rootNodeScreen->addButtonToScreen(optionsButton);
 
        this->addScreen(rootNodeScreen);
        this->setCurrentScreen(rootNodeScreen);
    }
};