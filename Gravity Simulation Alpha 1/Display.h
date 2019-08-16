#pragma once
#include <string>
#include <iostream>
#include <GLEW\glew.h>
#include <SDL2\SDL.h>
#undef main
using namespace std;

class Display
{
public:
	//Concstructor
	//Runs when class object is created
	Display(int width, int height, const string title);

	//Destructor
	//Runs when class is destoyed / ended
	virtual ~Display();

	//Function Declarations
	void ChangeBuffer();
	bool IsOpen();
	//void ProcessInput(); - Sent to input manager

private:
	//Pointer variable to the window
	SDL_Window* m_Window;

	//Create GL context to give GPU control of the window
	SDL_GLContext m_glContext;

	//Variable to store whether the window is open
	bool isOpen;

};

