#ifndef LOGIC_FOR_GAME_HEADER
#define LOGIC_FOR_GAME_HEADER

#include "IM_GUI_OBJ.h"

#include "logic_for_game.h"

#include "resource_manager.h"

#include "render_object.h"

#include <iostream>

// Game class that stores all game related states/functionality
class GAME_OBJ
{
public:

	GAME_OBJ(unsigned int width_of_window, unsigned int height_of_window); // constructor with arguments required to create a GAME_OBJ object
	~GAME_OBJ(); // deconstructor of GAME_OBJ

	unsigned int Width_Of_Screen, Height_Of_Screen; // stores the width and height of the actual game window

	// initalize the current state of the game (load all the shaders, textures, and levels)
	void Initalize_Game();

	void Render_Game(); // renders the game on the players screen
};




#endif // !LOGIC_FOR_GAME_HEADER
