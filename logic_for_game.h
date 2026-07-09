#ifndef LOGIC_FOR_GAME_HEADER
#define LOGIC_FOR_GAME_HEADER

#include "IM_GUI_OBJ.h"

#include "logic_for_game.h"

#include "resource_manager.h"

#include "render_object.h"

#include "process_shadow_map.h"

#include "cam.h"

#include "physics_object.h"

#include <reactphysics3d/reactphysics3d.h>
#include <reactphysics3d/collision/OverlapCallback.h>


#include <iostream>

// Game class that stores all game related states/functionality
class GAME_OBJ
{
public:

	GAME_OBJ(unsigned int width_of_window, unsigned int height_of_window); // constructor with arguments required to create a GAME_OBJ object
	~GAME_OBJ(); // deconstructor of GAME_OBJ


	bool		 Key_Pressed_Buffer[1024]; // buffer that stores key's that are pressed by player
	bool		 Processed_Keys[1024];    //  buffer that stores key's that have been processed
	bool		 Mouse_Button_Pressed_Buffer[1024]; // buffer that stores button's that are pressed by player
	bool		 Processed_Mouse_Button[1024]; // buffer that stores buttons that have been processed


	bool		 Mouse_Moved; // boolean value that tells if mouse has moved or not


	unsigned int Width_Of_Screen, Height_Of_Screen; // stores the width and height of the actual game window

	// where the last yaw position that was grabbed from the callback function is stored
	float last_mouse_yaw_position;
	// where the last pitch position that was grabbed from the callback function is stored
	float last_mouse_pitch_position;

	float flt_raw_mouse_yaw;

	float flt_raw_mouse_pitch;


	void Process_User_Input(float delta_time); // function that processes keys/movement done by player

	// initalize the current state of the game (load all the shaders, textures, and levels)
	void Initalize_Game();

	void Update_Game(float delta_time); // updates game to reflect prior user/movement and state of ball

	void Mouse_Velocity_Physics(bool mouse_moved_argument);

	void Render_Game(); // renders the game on the players screen
};


#endif // !LOGIC_FOR_GAME_HEADER
