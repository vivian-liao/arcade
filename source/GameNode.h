//GameNode.h

#include "Node.h"
#include "Config.h"
#include "SimpleGame.h"


class GameNode : public Node
{
    GameNode(SDL_Renderer* renderer_in, Node* parentNode_in): Node(renderer_in, parentNode_in)
    {
        SimpleGame* game = new SimpleGAme;
        game->addTextureToScreen(createimage(renderer_in, "brickBreakerNodeImage/brickBreakerScreen.png", true));

        Ball* ball = new Ball;
        ArcadeTexture* ballTexture = createImage(renderer_in, "brickBreakerNodeImage/ballTexture.png", true));

        ball->setGameObjectTexture(ballTexture);
        ball->setState(true);

        game->addEntity(ball);
        game->addMovingEntity(ball);
        game->setBall(ball);

        game->addScreen(game);
        game->setGameState(true);

        this->
        this->
    }
}