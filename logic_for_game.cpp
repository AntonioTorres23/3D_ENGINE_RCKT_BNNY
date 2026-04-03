#include "logic_for_game.h"


float amount_of_fov = 60.0f; 

glm::vec3 world_position_of_camera(0.0f, 0.0f, -8.0f);

RENDER_OBJECT_OBJ *render_obj; 
RENDER_OBJECT_OBJ *render_obj_plane;
RENDER_OBJECT_OBJ *skybox_obj;

GAME_OBJ::GAME_OBJ(unsigned int width_of_window, unsigned int height_of_window)
	: Width_Of_Screen(width_of_window), Height_Of_Screen(height_of_window)
{

}

GAME_OBJ::~GAME_OBJ()
{
	delete render_obj;
	delete render_obj_plane;
}

void GAME_OBJ::Initalize_Game()
{
	

	glm::mat4 view_matrix = glm::lookAt(glm::vec3(0.0f, 0.0f, -8.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 perspective_matrix = glm::perspective(glm::radians(90.0f), static_cast<float>(this->Width_Of_Screen) / static_cast<float>(this->Height_Of_Screen), 0.1f, 100.0f);


	RESOURCE_MANAGER::Shader_Load("shaders/3D_TEST.vert", "shaders/3D_TEST.frag", nullptr, "test");
	RESOURCE_MANAGER::Shader_Load("shaders/skybox.vert", "shaders/skybox.frag", nullptr, "skybox_test");

	RESOURCE_MANAGER::Texture_Load("assets/PTP-Stone_01-128x128.png", false, "texture");

	RESOURCE_MANAGER::Skybox_Textures_Load("assets/Classic", false, "skybox");

	RESOURCE_MANAGER::Shader_Get("test").Activate().uniform_integer("texture_image", 0);
	RESOURCE_MANAGER::Shader_Get("test").uniform_matrix_4("view_matrix", view_matrix);
	RESOURCE_MANAGER::Shader_Get("test").uniform_matrix_4("perspective_matrix", perspective_matrix);

	RESOURCE_MANAGER::Shader_Get("skybox_test").Activate().uniform_integer("skybox_texture", 0);
	RESOURCE_MANAGER::Shader_Get("skybox_test").uniform_matrix_4("view_matrix", view_matrix);
	RESOURCE_MANAGER::Shader_Get("skybox_test").uniform_matrix_4("perspective_matrix", perspective_matrix);


	// WORKS
	//render_obj = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("test"), PLANE);

	// IN TESTING
	render_obj = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("test"), CUBE);
	render_obj_plane = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("test"), PLANE);
	skybox_obj = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("skybox_test"), SKYBOX);
}


void GAME_OBJ::Render_Game()
{
	ImGui::Text("DEBUG");
	ImGui::SliderFloat("FOV", &amount_of_fov, 60.0f, 120.0f);
	glm::mat4 perspective_matrix = glm::perspective(glm::radians(amount_of_fov), static_cast<float>(this->Width_Of_Screen) / static_cast<float>(this->Height_Of_Screen), 0.1f, 100.0f);
	RESOURCE_MANAGER::Shader_Get("test").uniform_matrix_4("perspective_matrix", perspective_matrix);
	
	ImGui::SliderFloat("World X Position", &world_position_of_camera.x, -20.0f, 20.0f);
	ImGui::SliderFloat("World Y Position", &world_position_of_camera.y, -20.0f, 20.0f);
	ImGui::SliderFloat("World Z Position", &world_position_of_camera.z, -20.0f, 20.0f);

	glm::mat4 view_matrix = glm::lookAt(glm::vec3(world_position_of_camera.x, world_position_of_camera.y, world_position_of_camera.z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	RESOURCE_MANAGER::Shader_Get("test").uniform_matrix_4("view_matrix", view_matrix);

	render_obj->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture"), glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(5.0f), (100 * glfwGetTime()));
	render_obj->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture"), glm::vec3(7.0f, 0.0f, 3.0f), glm::vec3(5.0f), (100 * glfwGetTime()));
	render_obj_plane->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture"), glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(5.0f));

	skybox_obj->Render_and_Draw_Object(RESOURCE_MANAGER::Skybox_Textures_Get("skybox"));
}