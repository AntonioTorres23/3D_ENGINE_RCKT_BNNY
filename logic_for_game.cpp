#include "logic_for_game.h"

#include "resource_manager.h"

#include "render_object.h"

#include <iostream>

RENDER_OBJECT_OBJ *render_obj; 
RENDER_OBJECT_OBJ *render_obj_plane;

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
	glm::mat4 view_matrix = glm::lookAt(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 perspective_matrix = glm::perspective(glm::radians(90.0f), static_cast<float>(this->Width_Of_Screen) / static_cast<float>(this->Height_Of_Screen), 0.1f, 100.0f);


	RESOURCE_MANAGER::Shader_Load("3D_TEST.vert", "3D_TEST.frag", nullptr, "test");
	RESOURCE_MANAGER::Texture_Load("PTP-Stone_01-128x128.png", false, "texture");

	RESOURCE_MANAGER::Shader_Get("test").Activate().uniform_integer("texture_image", 0);
	RESOURCE_MANAGER::Shader_Get("test").uniform_matrix_4("view_matrix", view_matrix);
	RESOURCE_MANAGER::Shader_Get("test").uniform_matrix_4("perspective_matrix", perspective_matrix);

	// WORKS
	//render_obj = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("test"), PLANE);

	// IN TESTING
	render_obj = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("test"), CUBE);
	render_obj_plane = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("test"), PLANE);
}


void GAME_OBJ::Render_Game()
{
	render_obj->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture"), glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(5.0f), (100 * glfwGetTime()));
	render_obj_plane->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture"), glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(5.0f));
}