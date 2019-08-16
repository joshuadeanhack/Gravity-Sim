#include "InputManager.h"

InputManager::InputManager()
{
}

int InputManager::SimProcessInput()
{
	//Handle window events
	//Create OS event
	SDL_Event e;
	while (SDL_PollEvent(&e)) //Check for OS events found, event pass ByRef
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return 0; //Close window
		//case SDL_MOUSEMOTION:
			//cout<< e.motion.x <<" " << e.motion.y << endl;
		}
	}
	return -1;
}

int InputManager::MenuProcessInput()
{
	// Check Menu Input here
	// Mouse Over for white text to blue
	// Mouse Down check for normailsed button positions
	// Check for text input into textboxes

	return -1;
}