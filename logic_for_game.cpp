#include "logic_for_game.h"


// prototype for shadow mapping function only relevant to this C++ file
void Render_Shadows(SHADOW_MAP_OBJ &shadow_mapping_object_argument);

float amount_of_fov = 60.0f; 

glm::vec3 model_position(0.0f, 0.0f, 0.0f);

glm::vec3 cube_position_1(0.0f, 0.5f, 0.0f);

glm::vec3 cube_position_2(5.0f, 0.5f, 0.0f);

int orthographic_matrix = 30;


glm::vec3 world_position_of_camera(0.0f, 0.0f, 15.0f);
glm::vec3 directional_lighting_facing_direction(-2.0f, 4.0f, -1.0f);
glm::vec3 shadow_map_facing_position(20.0f, 40.0f, 20.0f);

float model_scale_size = 0.5f;

float near_plane_shadow = 0.1f, far_plane_shadow = 150.0f;

float ambient_color_values[3] =
{
	0.3f, 0.3f, 0.3f
};

float diffuse_color_values[3]
{
	0.6f, 0.6f, 0.6f
};

float specular_color_values[3]
{
	1.0f, 1.0f, 1.0f
};

RENDER_OBJECT_OBJ *render_obj; 
RENDER_OBJECT_OBJ *render_obj_plane;
RENDER_OBJECT_OBJ *skybox_obj;
RENDER_OBJECT_OBJ *model_obj;
RENDER_OBJECT_OBJ *model_obj_2;
SHADOW_MAP_OBJ *shadow_map;


GAME_OBJ::GAME_OBJ(unsigned int width_of_window, unsigned int height_of_window)
	: Width_Of_Screen(width_of_window), Height_Of_Screen(height_of_window)
{

}

GAME_OBJ::~GAME_OBJ()
{
	delete render_obj;
	delete render_obj_plane;
	delete skybox_obj;
	delete model_obj;
}

void GAME_OBJ::Initalize_Game()
{
	//SHADOW_MAP_OBJ shadow_map(1024, 1024);


	//glm::mat4 orthographic_light_perspective_matrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane_shadow, far_plane_shadow);
	//glm::mat4 light_view_matrix = glm::lookAt(directional_lighting_facing_direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//glm::mat4 light_matrix_for_shadow_mapping = orthographic_light_perspective_matrix * light_view_matrix;


	//glm::mat4 view_matrix = glm::lookAt(glm::vec3(0.0f, 0.0f, -8.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//glm::mat4 perspective_matrix = glm::perspective(glm::radians(90.0f), static_cast<float>(this->Width_Of_Screen) / static_cast<float>(this->Height_Of_Screen), 0.1f, 100.0f);

	// transforming this 4x4 matrix to a 3x3 with no values in the 4th column to prevent w coordinate from making translations
	//glm::mat4 skybox_view_matrix = glm::mat4(glm::mat3(view_matrix));

	//RESOURCE_MANAGER::Shader_Load("shaders/3D_TEST.vert", "shaders/3D_TEST.frag", nullptr, "test");
	//RESOURCE_MANAGER::Shader_Load("shaders/BLINN_PHONG_LIGHTING.vert", "shaders/BLINN_PHONG_LIGHTING.frag", nullptr, "test");
	RESOURCE_MANAGER::Shader_Load("shaders/BLINN_PHONG_LIGHTING_W_SHADOW_MAPPING.vert", "shaders/BLINN_PHONG_LIGHTING_W_SHADOW_MAPPING.frag", nullptr, "test");

	RESOURCE_MANAGER::Shader_Load("shaders/skybox.vert", "shaders/skybox.frag", nullptr, "skybox_test");


	//RESOURCE_MANAGER::Shader_Load("shaders/model_test.vert", "shaders/model_test.frag", nullptr, "model_test");
	RESOURCE_MANAGER::Shader_Load("shaders/BLINN_PHONG_LIGHTING_W_SHADOW_MAPPING.vert", "shaders/BLINN_PHONG_LIGHTING_W_SHADOW_MAPPING.frag", nullptr, "model_test");

	RESOURCE_MANAGER::Shader_Load("shaders/DEPTH_SHADER.vert", "shaders/DEPTH_SHADER.frag", nullptr, "depth_map_shader");



	RESOURCE_MANAGER::Texture_Load("assets/PTP-Pattern_03-128x128.png", false, "texture");
	//RESOURCE_MANAGER::Texture_Load("assets/PTP-Tile_05-128x128.png", false, "texture_2");
	RESOURCE_MANAGER::Texture_Load("assets/arcade_carpet_2_512.png", false, "texture_2");
	
	RESOURCE_MANAGER::Skybox_Textures_Load("assets/Classic", false, "skybox");
	RESOURCE_MANAGER::Skybox_Textures_Load("assets/Empty_Space", false, "skybox_2");


	//shadow_map = new SHADOW_MAP_OBJ(1024, 1024);


	//RESOURCE_MANAGER::Shader_Get("depth_map_shader").Activate().uniform_matrix_4("light_matrix_for_shadow_mapping", light_matrix_for_shadow_mapping);


	//RESOURCE_MANAGER::Shader_Get("test").uniform_matrix_4("light_matrix_for_shadow_mapping", light_matrix_for_shadow_mapping);
	//RESOURCE_MANAGER::Shader_Get("test").Activate().uniform_integer("texture_image", 0);
	//RESOURCE_MANAGER::Shader_Get("test").uniform_integer("shadowDepthMapTexture", shadow_map->texture_ID);
	//RESOURCE_MANAGER::Shader_Get("test").uniform_matrix_4("view_matrix", view_matrix);
	//RESOURCE_MANAGER::Shader_Get("test").uniform_matrix_4("perspective_matrix", perspective_matrix);

	//RESOURCE_MANAGER::Shader_Get("skybox_test").Activate().uniform_integer("skybox_texture", 0);
	//RESOURCE_MANAGER::Shader_Get("skybox_test").uniform_matrix_4("view_matrix", skybox_view_matrix);
	//RESOURCE_MANAGER::Shader_Get("skybox_test").uniform_matrix_4("perspective_matrix", perspective_matrix);
	

	/*
	glActiveTexture(GL_TEXTURE12);
	glBindTexture(GL_TEXTURE_2D, shadow_map->texture_ID);
	RESOURCE_MANAGER::Shader_Get("model_test").uniform_integer("shadowDepthMapTexture", 12);
	*/


	//RESOURCE_MANAGER::Shader_Get("model_test").uniform_matrix_4("light_matrix_for_shadow_mapping", light_matrix_for_shadow_mapping);
	//RESOURCE_MANAGER::Shader_Get("model_test").Activate().uniform_integer("shadowDepthMapTexture", shadow_map->texture_ID);
	//RESOURCE_MANAGER::Shader_Get("model_test").uniform_matrix_4("view_matrix", view_matrix);
	//RESOURCE_MANAGER::Shader_Get("model_test").uniform_matrix_4("perspective_matrix", perspective_matrix);


	render_obj = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), CUBE);
	render_obj_plane = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), PLANE);
	skybox_obj = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("skybox_test"), SKYBOX);

	model_obj = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/quaddamage/quaddamage.dae", "quad_damage", true);

	//model_obj_2 = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/survival-guitar-backpack/source/Survival_BackPack_2/Survival_BackPack_2.fbx", "quad_damage", true);

	//model_obj_2 = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/1965_MB_560_SEC_obj/d4411c08-dfa1-4727-a541-ef9bd7bde35a.obj", "quad_damage", true);

	//model_obj_2 = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/PentagramofProtection/invulner.obj", "survival_backpack", true);
	//model_obj_2 = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/B.D. Joe/B.D. Joe.obj", "quad_damage", false);
	model_obj_2 = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/B.D. Joe/B.D. Joe.obj", "quad_damage", false);
	
	shadow_map = new SHADOW_MAP_OBJ(1024, 1024);

	//glActiveTexture(GL_TEXTURE18);
	//glBindTexture(GL_TEXTURE_2D, shadow_map->texture_ID);
	//RESOURCE_MANAGER::Shader_Get("model_test").uniform_integer("shadowDepthMapTexture", 18);
	
}


void GAME_OBJ::Render_Game()
{
	ImGui::Text("DEBUG");

	ImGui::Text("World View Settings");

	ImGui::SliderFloat("FOV", &amount_of_fov, 60.0f, 120.0f);


	ImGui::SliderFloat("World X Position", &world_position_of_camera.x, -100.0f, 100.0f);
	ImGui::SliderFloat("World Y Position", &world_position_of_camera.y, -100.0f, 100.0f);
	ImGui::SliderFloat("World Z Position", &world_position_of_camera.z, -100.0f, 100.0f);


	ImGui::Text("Lighting Settings");

	ImGui::SliderFloat("Light X Direction", &directional_lighting_facing_direction.x, -50.0f, 0.0f);
	ImGui::SliderFloat("Light Y Direction", &directional_lighting_facing_direction.y, -50.0f, 50.0f);
	ImGui::SliderFloat("Light Z Direction", &directional_lighting_facing_direction.z, -50.0f, 0.0f);

	ImGui::SliderInt("Orthographic Matrix", &orthographic_matrix, 0, 1000);

	// To store color picker values, you need a 3-value float array

	//ImGui::SliderFloat3("test", a, 0.0f, 1.0f);
	ImGui::SetNextItemWidth(200.0f);
	ImGui::ColorPicker3("Ambient Color", ambient_color_values);
	ImGui::SetNextItemWidth(200.0f);
	ImGui::ColorPicker3("Diffuse Color", diffuse_color_values);
	ImGui::SetNextItemWidth(200.0f);
	ImGui::ColorPicker3("Specular Color", specular_color_values);

	ImGui::SliderFloat("NEAR_SHADOW_PLANE", &near_plane_shadow, -100.0f, 100.0f);
	ImGui::SliderFloat("FAR_SHADOW_PLANE", &far_plane_shadow, -100.0f, 100.0f);

	ImGui::SliderFloat("Model X Direction", &model_position.x, -50.0f, 50.0f);

	ImGui::SliderFloat("Model Y Direction", &model_position.y, -50.0f, 50.0f);


	ImGui::SliderFloat("Model Z Direction", &model_position.z, -50.0f, 50.0f);

	ImGui::SliderFloat("Model Scale Size", &model_scale_size, -100.0f, 100.0f);

	ImGui::SliderFloat("CUBE 1  X Direction", &cube_position_1.x, -50.0f, 50.0f);

	ImGui::SliderFloat("CUBE 1  Y Direction", &cube_position_1.y, -50.0f, 50.0f);


	ImGui::SliderFloat("CUBE 1  Z Direction", &cube_position_1.z, -50.0f, 50.0f);



	ImGui::SliderFloat("CUBE 2  X Direction", &cube_position_2.x, -50.0f, 50.0f);

	ImGui::SliderFloat("CUBE 2  Y Direction", &cube_position_2.y, -50.0f, 50.0f);


	ImGui::SliderFloat("CUBE 2  Z Direction", &cube_position_2.z, -50.0f, 50.0f);



	glm::mat4 view_matrix = glm::lookAt(glm::vec3(world_position_of_camera.x, world_position_of_camera.y, world_position_of_camera.z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//glm::mat4 orthographic_light_perspective_matrix = glm::ortho(-(static_cast<float>(orthographic_matrix)), (static_cast<float>(orthographic_matrix)), -(static_cast<float>(orthographic_matrix)), (static_cast<float>(orthographic_matrix)), near_plane_shadow, far_plane_shadow);
	glm::mat4 orthographic_light_perspective_matrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 150.0f);
	glm::mat4 light_view_matrix = glm::lookAt(directional_lighting_facing_direction * -1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 perspective_matrix = glm::perspective(glm::radians(amount_of_fov), static_cast<float>(this->Width_Of_Screen) / static_cast<float>(this->Height_Of_Screen), 0.1f, 100.0f);

	glm::mat4 light_matrix_for_shadow_mapping = orthographic_light_perspective_matrix * light_view_matrix;

	light_matrix_for_shadow_mapping = orthographic_light_perspective_matrix * light_view_matrix;

	
	// transforming this 4x4 matrix to a 3x3 with no values in the 4th column to prevent w coordinate from making translations
	glm::mat4 skybox_view_matrix = glm::mat4(glm::mat3(view_matrix));

	/*
	RESOURCE_MANAGER::Shader_Get("depth_map_shader").Activate();
	render_obj->object_shader_obj = RESOURCE_MANAGER::Shader_Get("depth_map_shader");
	render_obj_plane->object_shader_obj = RESOURCE_MANAGER::Shader_Get("depth_map_shader");
	//model_obj->object_shader_obj = RESOURCE_MANAGER::Shader_Get("model_test");
	model_obj_2->object_shader_obj = RESOURCE_MANAGER::Shader_Get("depth_map_shader");

	RESOURCE_MANAGER::Shader_Get("depth_map_shader").uniform_matrix_4("light_matrix_for_shadow_mapping", light_matrix_for_shadow_mapping);
	*/

	RESOURCE_MANAGER::Shader_Get("depth_map_shader").Activate();
	render_obj->object_shader_obj = RESOURCE_MANAGER::Shader_Get("depth_map_shader");
	render_obj_plane->object_shader_obj = RESOURCE_MANAGER::Shader_Get("depth_map_shader");
	//model_obj->object_shader_obj = RESOURCE_MANAGER::Shader_Get("model_test");
	model_obj_2->object_shader_obj = RESOURCE_MANAGER::Shader_Get("depth_map_shader");

	RESOURCE_MANAGER::Shader_Get("depth_map_shader").Activate().uniform_matrix_4("light_matrix_for_shadow_mapping", light_matrix_for_shadow_mapping);
	// set viewport to shadow map's texture dimensions
	glViewport(0, 0, shadow_map->width_of_texture, shadow_map->height_of_texture);
	// bind depth framebuffer object
	glBindFramebuffer(GL_FRAMEBUFFER, shadow_map->depth_map_frame_buffer_object);
	// clear depth buffer
	glClear(GL_DEPTH_BUFFER_BIT);

	//glEnable(GL_DEPTH_TEST);
	//glCullFace(GL_FRONT);


	//model_obj_2->Render_and_Draw_Object(glm::vec3(model_position), glm::vec3(model_scale_size), (100 * glfwGetTime()));
	//render_obj_plane->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture_2"), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	
	render_obj->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture"), glm::vec3(cube_position_1), glm::vec3(0.5), (100 * glfwGetTime()));
	render_obj->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture"), glm::vec3(cube_position_2), glm::vec3(0.5f), (100 * glfwGetTime()));

	
	//render_obj_plane->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture_2"), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	model_obj_2->Render_and_Draw_Object(glm::vec3(model_position), glm::vec3(model_scale_size), (100 * glfwGetTime()));

	

	//glCullFace(GL_BACK);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	glViewport(0, 0, this->Width_Of_Screen, this->Height_Of_Screen);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	RESOURCE_MANAGER::Shader_Get("model_test").Activate();
	render_obj->object_shader_obj = RESOURCE_MANAGER::Shader_Get("model_test");
	render_obj_plane->object_shader_obj = RESOURCE_MANAGER::Shader_Get("model_test");
	model_obj->object_shader_obj = RESOURCE_MANAGER::Shader_Get("model_test");
	model_obj_2->object_shader_obj = RESOURCE_MANAGER::Shader_Get("model_test");


	// SEND MODEL MATRICES HERE 
		// you must specify the index of the color picker array individually to send the values via a uniform
	// remember that within the uniform vector member functions within a SHADER_OBJ they are overloaded to either take a glm vector or individual x, y, or z float values
	RESOURCE_MANAGER::Shader_Get("model_test").uniform_vector_3("directional_lighting_obj.light_direction", directional_lighting_facing_direction);
	glActiveTexture(GL_TEXTURE18);
	glBindTexture(GL_TEXTURE_2D, shadow_map->texture_ID);
	RESOURCE_MANAGER::Shader_Get("model_test").uniform_integer("shadowDepthMapTexture", 18);
	RESOURCE_MANAGER::Shader_Get("model_test").uniform_matrix_4("light_matrix_for_shadow_mapping", light_matrix_for_shadow_mapping);
	
	RESOURCE_MANAGER::Shader_Get("model_test").uniform_matrix_4("view_matrix", view_matrix);
	RESOURCE_MANAGER::Shader_Get("model_test").uniform_matrix_4("perspective_matrix", perspective_matrix);
	RESOURCE_MANAGER::Shader_Get("model_test").uniform_vector_3("camera_world_position", world_position_of_camera);




	RESOURCE_MANAGER::Shader_Get("model_test").uniform_vector_3("directional_lighting_obj.ambient_color", ambient_color_values[0], ambient_color_values[1], ambient_color_values[2]);
	RESOURCE_MANAGER::Shader_Get("model_test").uniform_vector_3("directional_lighting_obj.diffuse_color", diffuse_color_values[0], diffuse_color_values[1], diffuse_color_values[2]);
	RESOURCE_MANAGER::Shader_Get("model_test").uniform_vector_3("directional_lighting_obj.specular_color", specular_color_values[0], specular_color_values[1], specular_color_values[2]);



	// enable depth function so that it passes vertices that are equal to depth buffer's content
	glDepthFunc(GL_LEQUAL);

	skybox_obj->Render_and_Draw_Object(RESOURCE_MANAGER::Skybox_Textures_Get("skybox_2"));



	// set depth func back to original state which is GL_LESS
	glDepthFunc(GL_LESS);

	// PUT SKYBOX MATRICES HERE
	RESOURCE_MANAGER::Shader_Get("skybox_test").uniform_matrix_4("skybox_view_matrix", skybox_view_matrix);
	RESOURCE_MANAGER::Shader_Get("skybox_test").uniform_matrix_4("perspective_matrix", perspective_matrix);

	//model_obj_2->Render_and_Draw_Object(glm::vec3(model_position), glm::vec3(model_scale_size), (100 * glfwGetTime()));
	render_obj_plane->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture_2"), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	render_obj->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture"), glm::vec3(cube_position_1), glm::vec3(0.5f), (100 * glfwGetTime()));
	render_obj->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture"), glm::vec3(cube_position_2), glm::vec3(0.5f), (100 * glfwGetTime()));
	//render_obj_plane->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture_2"), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	model_obj_2->Render_and_Draw_Object(glm::vec3(model_position), glm::vec3(model_scale_size), (100 * glfwGetTime()));

}



void Render_Shadows(SHADOW_MAP_OBJ &shadow_mapping_object_argument)
{
	// set viewport to shadow map's texture dimensions
	glViewport(0, 0, shadow_mapping_object_argument.width_of_texture, shadow_mapping_object_argument.height_of_texture);
	// bind depth framebuffer object
	glBindFramebuffer(GL_FRAMEBUFFER, shadow_mapping_object_argument.depth_map_frame_buffer_object);
	// clear depth buffer
	glClear(GL_DEPTH_BUFFER_BIT);

}