#include "Display.h"

Display::Display(int width, int height, const string title)
{
	//Initalise the SDL to create the window
	SDL_Init(SDL_INIT_EVERYTHING);

	//SDL_WINDOW_OPENGL
	//Set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Shades of red 2^8 = 256 shades
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); //Shades of green 2^8 
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); //Shades of blue 2^8 
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); //Transparency values 2^8

	//Sets at least 32 bits for colour buffer
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //32 bits

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //Allocate space for 2 windows/buffers
	//Used for buffer swapping
	//Second window/buffer won't be displayed 

	/* Enable multisampling for a nice antialiased effect */
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);


	//Create window
	m_Window = SDL_CreateWindow(
		title.c_str(), //Convert C++ string to C sting char array
		SDL_WINDOWPOS_CENTERED, //Center the window X
		SDL_WINDOWPOS_CENTERED, //Center the window Y
		width, height,	//Set X and Y 
		SDL_WINDOW_OPENGL); // Flags, create window in different ways 
	//=> draw with opengl 

	//Give GPU control of window
	//Set up the GL context
	m_glContext = SDL_GL_CreateContext(m_Window);

	/*
	-----------
	NOW Initialise OPEN GL
	----------
	*/

	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		cerr << "Glew Failed To Initalize... What are you going to do now?" << endl;
	}

	//Now have access to OpenGL functions
	isOpen = true;
}

Display::~Display()
{
	//Delete context
	SDL_GL_DeleteContext(m_glContext);
	//Destroy window
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void Display::ChangeBuffer()
{
	/*This will swap the buffers around
	OPENGL has one memory buffer
	The window has another
	When OPENGL has finished drawing to its buffer
	Then the buffers are swapped
	so the window shows the memory OPENGL has just drawn to
	OpenGL will draw to the other buffer and they will swap again
	this is what updates the window
	----
	Used so that you don't see objects that are still being
	drawn to the screen
	*/
	SDL_GL_SwapWindow(m_Window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
bool Display::IsOpen() {return isOpen;}

//void Display::ProcessInput()
//{	//Handle window events
//	//Create OS event
//	SDL_Event e;
//	while (SDL_PollEvent(&e)) //Check for OS events found, event pass ByRef
//	{
//		switch (e.type)
//		{
//		case SDL_QUIT:
//			isOpen = false; //Close window
//			//case SDL_MOUSEMOTION:
//			//	cout<< e.motion.x <<" " << e.motion.y << endl;
//		}
//	}
//}

