#ifndef CAM_HEADER
#define CAM_HEADER

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum KEYBOARD_MOVEMENT {
	W,
	S,
	A,
	D
};

extern float CAM_YAW; // default value of how left or right we are looking in our view vector, set to -90 by default to look towards negative z-axis
extern float CAM_PITCH; // default value of how up or down we are looing in our view vector, set to 0 by default for no effect at first
extern float CAM_SPEED; // global value of how fast we want the camera to move within the world environment, will be multiplied to the keybindings
extern float MOUSE_SENS;  // global value of how fast we want our camera to move left, right, down, or up in terms of the view vector/when we move the mouse via call back

class CAM_OBJ
{
public:
	// public members that are stored with the Cam_AND_Mov OBJ
	glm::vec3 obj_cam_pos;
	glm::vec3 obj_cam_front_view;
	glm::vec3 obj_up;
	glm::vec3 obj_cam_right;
	glm::vec3 obj_cam_world_up;
	float obj_yaw;
	float obj_pitch;
	float obj_cam_speed;
	float obj_mouse_sens;

	// PROGRAMER'S NOTE: I THINK THAT WE INITIALIZE THE FRONT VECTOR RATHER THAN TAKE IT AS AN ARGUMENT BECAUSE IT WILL ALWAYS CONTAIN THE COORDINATES (0.0f, 0.0f, -1.0f) 
	// create a constructor with glm::vec3 variables importing or setting/initializing the values of the public methods before within this constructor
	// simply just creating values or importing them for the arguments then assigning them to the prior public methods
	CAM_OBJ(glm::vec3 arg_pos = glm::vec3(0.0f, 0.0f, 0.0), glm::vec3 arg_up = glm::vec3(0.0f, 1.0f, 0.0f), float arg_yaw = CAM_YAW, float arg_pitch = CAM_PITCH);

	// overloaded constructor if scalar x, y, z values are used for the position and world up vectors
	CAM_OBJ(float obj_pos_x_coord, float obj_pos_y_coord, float obj_pos_z_coord, float obj_up_x_coord, float obj_up_y_coord, float obj_up_z_coord, float arg_obj_yaw, float arg_obj_pitch);

	glm::mat4 Obtain_View_Matrix();

	void KEYBOARD(KEYBOARD_MOVEMENT key, float dTime);

	void MOUSE(float yaw_offset, float pitch_offset, GLboolean limitPitch = true);

private:

	void UPDATE_CAM_OBJ_VEC();
};

#endif // !CAM_HEADER

