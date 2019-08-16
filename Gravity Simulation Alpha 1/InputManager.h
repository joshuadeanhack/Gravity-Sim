#pragma once
#include <iostream>
#include <string>
#include <GLEW\glew.h>
#include <SDL2\SDL.h>
#undef main
using namespace std;
class InputManager
{
public:
	InputManager();

	int SimProcessInput();
	int MenuProcessInput();
};

