// main.cpp

#include "SDL.h"
#include "SDL_mixer.h"
#include "RootNode.h"
#include "Config.h"

// declaring pointer to objects that main needs, initialize to null
// these objects are created in main because they are needed for the outermost loop
SDL_Window* arcadeSystemWindow = nullptr;
SDL_Renderer* arcadeSystemRenderer = nullptr;
TTF_Font* font = nullptr;
Node* currentNode = nullptr;

// initialization function, initializes above objects and calls some SDL initialization functions
bool init()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create window in the center of the screen
		arcadeSystemWindow = SDL_CreateWindow("Arcade System", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
		if (arcadeSystemWindow == NULL)	
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// initialize renderer, set the background as white for the wwindow, sync the renderer with the monitor refresh rate
			arcadeSystemRenderer = SDL_CreateRenderer(arcadeSystemWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			SDL_SetRenderDrawColor(arcadeSystemRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		}
		// Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}
		// initialize true type font 
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}

	}
	return success;
}

int main(int argc, char* argv[])
{	
	// first call initialization
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	// if initializes successfully then continue
	else
	{
		// first create the root node which triggers creation of all nodes
 		RootNode rootNode(arcadeSystemRenderer, nullptr); 
		currentNode = &rootNode;

		Mix_Music* currentMusic = nullptr;
		bool soundState = false;

		// flag for main loop 
		bool quit = false;

		// main loop
		while (!quit)
		{	
			// handle events on queue until empty
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0)
			{
				// user requests quit by clicking window X
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				
				// start update process by handling the next event on the event queue
				Action newAction = currentNode->update(&e);
				
				// check to see if the event triggers an action is executed in this outermost loop
				switch (newAction.actionName)
				{
				case(MOVE_NODES):
				{
					// when moving nodes, first exit, set the current, then enter
					printf("\nMOVING NODES\n");
					currentNode->exitNode();
					currentNode = (Node*)(newAction.actionParameter);
					currentNode->enter();
					break;
				}
				case(CHANGE_SOUND):
				{
					// when changing sound to off, stop the music
					printf("\n changing sound\n\n");
					if (newAction.actionParameter == 0)
					{
						printf("\n sound turning off\n\n");
						Mix_HaltMusic();
						soundState = false;
					}
					else
					{
						soundState = true;
						printf("\n sound turning on\n\n");
						Mix_PlayMusic(currentMusic, -1);
					}
					break;
				}
				case(CHANGE_MUSIC):
				{
					// when changing music, check whether sound is on or not
					printf("\n changing music\n\n");
					printf("\n music pointer: %p\n\n", (Mix_Music*)(newAction.actionParameter));
					currentMusic = (Mix_Music*)(newAction.actionParameter);
					if (soundState == true)
					{
						if (currentMusic == nullptr)
						{
							Mix_HaltMusic();
						}
						else
						{
							Mix_PlayMusic(currentMusic, -1);
						}
					}
					break;
				}
				default:
					break;
				}
			}
			// after handling all events, update all graphics for animation
			currentNode->update(nullptr);

			// after updating, render
			currentNode->render(arcadeSystemRenderer);
			SDL_RenderPresent(arcadeSystemRenderer);
		}
	}
	// after quitting, free up SDL_Resources -- Note: rootNode was created on the stack so after quitting it will go
	// out of scope and its destructor will be called which triggers the destructors of all other nodes
	Mix_CloseAudio();
	TTF_CloseFont(font);
	SDL_DestroyRenderer(arcadeSystemRenderer);
	SDL_DestroyWindow(arcadeSystemWindow);

	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	return 0;
}