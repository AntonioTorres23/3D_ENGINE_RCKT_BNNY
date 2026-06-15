#include "logic_for_game.h"

const reactphysics3d::decimal ts = 1.0f / 60.0f;

reactphysics3d::PhysicsCommon physCom;
reactphysics3d::PhysicsWorld* physWorld = physCom.createPhysicsWorld();


float amount_of_fov = 60.0f; 

glm::vec3 model_position(-1.0f, 5.0f, 0.0f);

glm::vec3 cube_position_1(-5.0f, 10.0, 0.0f);

glm::vec3 cube_position_2(0.0f, 0.0f, 0.0f);

glm::vec3 floor_position(0.0f, 0.0f, 0.0f);

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

reactphysics3d::Vector3 POS(cube_position_1.x, cube_position_1.y, cube_position_1.z);
reactphysics3d::Quaternion quart = reactphysics3d::Quaternion::identity();
reactphysics3d::Transform trans(POS, quart);
reactphysics3d::RigidBody* bod_rigid = physWorld->createRigidBody(trans);

reactphysics3d::Vector3 POS2(cube_position_2.x, cube_position_2.y, cube_position_2.z);
reactphysics3d::Quaternion quart2 = reactphysics3d::Quaternion::identity();
reactphysics3d::Transform trans2(POS2, quart2);
reactphysics3d::RigidBody* bod_rigid2 = physWorld->createRigidBody(trans2);

reactphysics3d::Vector3 POS3(floor_position.x, floor_position.y, floor_position.z);
reactphysics3d::Quaternion quart3 = reactphysics3d::Quaternion::identity();
reactphysics3d::Transform trans3(POS3, quart3);
reactphysics3d::RigidBody* bod_rigid3 = physWorld->createRigidBody(trans3);


//reactphysics3d::Vector3 POS4;
//reactphysics3d::Quaternion quart4 = reactphysics3d::Quaternion::identity();
//reactphysics3d::Transform trans4(POS4, quart4);
//reactphysics3d::RigidBody* bod_rigid4 = physWorld->createRigidBody(trans4);


reactphysics3d::Vector3 HalfSpace(0.4, 0.4, 0.4);
reactphysics3d::Vector3 FloorHalfSpace(100.0, 1.0, 100.0);

reactphysics3d::BoxShape* BoxCollision = physCom.createBoxShape(HalfSpace);
reactphysics3d::BoxShape* FloorBoxCollision = physCom.createBoxShape(FloorHalfSpace);
reactphysics3d::CapsuleShape* PlayerCollision = physCom.createCapsuleShape(5.0, 8.0);

reactphysics3d::Collider* collider1 = bod_rigid->addCollider(BoxCollision, trans);

reactphysics3d::Collider* collider2 = bod_rigid2->addCollider(BoxCollision, trans2);

reactphysics3d::Collider* collider3 = bod_rigid3->addCollider(FloorBoxCollision, trans3);

//reactphysics3d::Collider* collider4 = bod_rigid4->addCollider(PlayerCollision, trans4);



RENDER_OBJECT_OBJ *render_obj; 
RENDER_OBJECT_OBJ *render_obj_plane;
RENDER_OBJECT_OBJ *skybox_obj;
RENDER_OBJECT_OBJ *model_obj;
RENDER_OBJECT_OBJ *model_obj_2;
SHADOW_MAP_OBJ *shadow_map;
CAM_OBJ *camera_obj;



GAME_OBJ::GAME_OBJ(unsigned int width_of_window, unsigned int height_of_window)
	: Width_Of_Screen(width_of_window), Height_Of_Screen(height_of_window)
{
	// where the last yaw position that was grabbed from the callback function is stored
	float last_mouse_yaw_position = Width_Of_Screen / 2.0f;
	// where the last pitch position that was grabbed from the callback function is stored
	float last_mouse_pitch_position = Height_Of_Screen / 2.0f;
}

GAME_OBJ::~GAME_OBJ()
{
	delete render_obj;
	delete render_obj_plane;
	delete skybox_obj;
	delete model_obj;
	delete model_obj_2;
	delete shadow_map;
	delete camera_obj;
}
void GAME_OBJ::Initalize_Game()
{

	bod_rigid->setType(reactphysics3d::BodyType::DYNAMIC);
	bod_rigid2->setType(reactphysics3d::BodyType::DYNAMIC);
	//bod_rigid4->setType(reactphysics3d::BodyType::DYNAMIC);
	bod_rigid3->setType(reactphysics3d::BodyType::STATIC);
	

	physWorld->setGravity(reactphysics3d::Vector3(0.0, -0.05, 0.0));

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
	RESOURCE_MANAGER::Texture_Load("assets/PTP-Tile_05-128x128.png", false, "texture_2");
	//RESOURCE_MANAGER::Texture_Load("assets/arcade_carpet_2_512.png", false, "texture_2");
	
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

	//model_obj = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/Counter-Terrorists_GIGN/COUNTER-TERRORIST_GIGN.obj", "quad_damage", false);
	model_obj = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/Dust2/Dust2.obj", "quad_damage", false);
	//model_obj_2 = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/survival-guitar-backpack/source/Survival_BackPack_2/Survival_BackPack_2.fbx", "quad_damage", true);

	//model_obj_2 = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/1965_MB_560_SEC_obj/d4411c08-dfa1-4727-a541-ef9bd7bde35a.obj", "quad_damage", true);

	//model_obj_2 = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/PentagramofProtection/invulner.obj", "survival_backpack", true);
	//model_obj_2 = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/B.D. Joe/B.D. Joe.obj", "quad_damage", false);
	model_obj_2 = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/B.D. Joe/B.D. Joe.obj", "quad_damage", false);
	
	shadow_map = new SHADOW_MAP_OBJ(1024, 1024);

	camera_obj = new CAM_OBJ(glm::vec3(1.0f, 5.0f, 0.0f));

	//POS4.x = camera_obj->obj_cam_pos.x;
	//POS4.y = camera_obj->obj_cam_pos.y;
	//POS4.z = camera_obj->obj_cam_pos.z;

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
	// To store color picker values, you need a 3-value float array

	//ImGui::SliderFloat3("test", a, 0.0f, 1.0f);
	ImGui::SetNextItemWidth(200.0f);
	ImGui::ColorPicker3("Ambient Color", ambient_color_values);
	ImGui::SetNextItemWidth(200.0f);
	ImGui::ColorPicker3("Diffuse Color", diffuse_color_values);
	ImGui::SetNextItemWidth(200.0f);
	ImGui::ColorPicker3("Specular Color", specular_color_values);
	ImGui::SetNextItemWidth(200.0f);
	ImGui::SliderInt("Ortographic Matrix Size", &orthographic_matrix, 10, 100);

	ImGui::SetNextItemWidth(200.0f);
	ImGui::SliderFloat("NEAR_SHADOW_PLANE", &near_plane_shadow, -100.0f, 100.0f);
	ImGui::SliderFloat("FAR_SHADOW_PLANE", &far_plane_shadow, -100.0f, 100.0f);
	ImGui::SetNextItemWidth(200.0f);
	//ImGui::SliderFloat("Model X Direction", &model_position.x, -50.0f, 50.0f);

	//ImGui::SliderFloat("Model Y Direction", &model_position.y, -50.0f, 50.0f);


	//ImGui::SliderFloat("Model Z Direction", &model_position.z, -50.0f, 50.0f);
	//ImGui::SetNextItemWidth(200.0f);
	//ImGui::SliderFloat("Model Scale Size", &model_scale_size, -100.0f, 100.0f);
	//ImGui::SetNextItemWidth(200.0f);
	//ImGui::SliderFloat("CUBE 1  X Direction", &cube_position_1.x, -50.0f, 50.0f);

	//ImGui::SliderFloat("CUBE 1  Y Direction", &cube_position_1.y, -50.0f, 50.0f);

	//ImGui::SliderFloat("CUBE 1  Z Direction", &cube_position_1.z, -50.0f, 50.0f);
	ImGui::SetNextItemWidth(200.0f);
	ImGui::SliderFloat("CUBE 2  X Direction", &cube_position_2.x, -50.0f, 50.0f);

	ImGui::SliderFloat("CUBE 2  Y Direction", &cube_position_2.y, -50.0f, 50.0f);


	ImGui::SliderFloat("CUBE 2  Z Direction", &cube_position_2.z, -50.0f, 50.0f);
	ImGui::SetNextItemWidth(200.0f);
	//glm::mat4 view_matrix = glm::lookAt(glm::vec3(world_position_of_camera.x, world_position_of_camera.y, world_position_of_camera.z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 view_matrix = camera_obj->Obtain_View_Matrix();


	//glm::mat4 orthographic_light_perspective_matrix = glm::ortho(-(static_cast<float>(orthographic_matrix)), (static_cast<float>(orthographic_matrix)), -(static_cast<float>(orthographic_matrix)), (static_cast<float>(orthographic_matrix)), near_plane_shadow, far_plane_shadow);
	glm::mat4 orthographic_light_perspective_matrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 150.0f);
	glm::mat4 light_view_matrix = glm::lookAt(directional_lighting_facing_direction * -1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 perspective_matrix = glm::perspective(glm::radians(amount_of_fov), static_cast<float>(this->Width_Of_Screen) / static_cast<float>(this->Height_Of_Screen), 0.1f, 100.0f);

	glm::mat4 light_matrix_for_shadow_mapping = orthographic_light_perspective_matrix * light_view_matrix;

	light_matrix_for_shadow_mapping = orthographic_light_perspective_matrix * light_view_matrix;

	
	// transforming this 4x4 matrix to a 3x3 with no values in the 4th column to prevent w coordinate from making translations
	glm::mat4 skybox_view_matrix = glm::mat4(glm::mat3(view_matrix));

	RESOURCE_MANAGER::Shader_Get("depth_map_shader").Activate();
	render_obj->object_shader_obj = RESOURCE_MANAGER::Shader_Get("depth_map_shader");
	render_obj_plane->object_shader_obj = RESOURCE_MANAGER::Shader_Get("depth_map_shader");
	//model_obj->object_shader_obj = RESOURCE_MANAGER::Shader_Get("depth_map_shader");
	//model_obj_2->object_shader_obj = RESOURCE_MANAGER::Shader_Get("depth_map_shader");

	RESOURCE_MANAGER::Shader_Get("depth_map_shader").Activate().uniform_matrix_4("light_matrix_for_shadow_mapping", light_matrix_for_shadow_mapping);
	// set viewport to shadow map's texture dimensions
	glViewport(0, 0, shadow_map->width_of_texture, shadow_map->height_of_texture);
	// bind depth framebuffer object
	glBindFramebuffer(GL_FRAMEBUFFER, shadow_map->depth_map_frame_buffer_object);
	// clear depth buffer
	glClear(GL_DEPTH_BUFFER_BIT);
	
	render_obj_plane->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture_2"), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	render_obj->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture"), glm::vec3(cube_position_1), glm::vec3(0.5), (100 * glfwGetTime()));
	render_obj->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture"), glm::vec3(cube_position_2), glm::vec3(0.5f), (100 * glfwGetTime()));
	//render_obj->Render_and_Draw_Object(RESOURCE_MANAGER::Texture_Get("texture"), glm::vec3(cube_position_2), glm::vec3(0.5f), (100 * glfwGetTime()));
	//model_obj_2->Render_and_Draw_Object(glm::vec3(model_position), glm::vec3(model_scale_size), (100 * glfwGetTime()));
	//model_obj->Render_and_Draw_Object(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

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
	//model_obj_2->Render_and_Draw_Object(glm::vec3(model_position), glm::vec3(model_scale_size), (100 * glfwGetTime()));
	//model_obj->Render_and_Draw_Object(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//model_obj->Render_and_Draw_Object(glm::vec3(-1.0f, 0.0f, -0.5f), glm::vec3(1.0f), (100 * glfwGetTime()));
	//model_obj->Render_and_Draw_Object(glm::vec3(2.0f, 0.0f, 1.0f), glm::vec3(1.0f), (100 * glfwGetTime()));
	//model_obj->Render_and_Draw_Object(glm::vec3(-2.0f, 0.0f, -1.0f), glm::vec3(1.0f), (100 * glfwGetTime()));
}

void GAME_OBJ::Process_User_Input(float delta_time)
{

	if (this->Key_Pressed_Buffer[GLFW_KEY_W])
		camera_obj->obj_cam_pos += camera_obj->obj_cam_front_view * camera_obj->obj_cam_speed;
	if (this->Key_Pressed_Buffer[GLFW_KEY_A])
		camera_obj->obj_cam_pos -= camera_obj->obj_cam_right * camera_obj->obj_cam_speed;
	if (this->Key_Pressed_Buffer[GLFW_KEY_S])
		camera_obj->obj_cam_pos -= camera_obj->obj_cam_front_view * camera_obj->obj_cam_speed;
	if (this->Key_Pressed_Buffer[GLFW_KEY_D])
		camera_obj->obj_cam_pos += camera_obj->obj_cam_right * camera_obj->obj_cam_speed;
	if (this->Key_Pressed_Buffer[GLFW_KEY_SPACE])
		camera_obj->obj_cam_pos.y += 50;
	

	// subtracts the difference of the yaw position last stored and the current yaw position that was called. 
	float mouse_yaw_offset = last_mouse_yaw_position - flt_raw_mouse_yaw;
	// subtracts the difference of the pitch position last stored and the current pitch position that was called.
	float mouse_pitch_offset = flt_raw_mouse_pitch - last_mouse_pitch_position;
	// set the yaw position that was just called as the last yaw position
	// this gets us set up for the next time this function is called
	last_mouse_yaw_position = flt_raw_mouse_yaw;
	// sets the pitch position that was just called as the last pitch position
	// this gets us set up for the next time this function is called 
	last_mouse_pitch_position = flt_raw_mouse_pitch;

	camera_obj->MOUSE(mouse_yaw_offset, mouse_pitch_offset);

}

void GAME_OBJ::Update_Game(float delta_time)
{
	
	GAME_OBJ::Process_User_Input(delta_time);


	//const reactphysics3d::decimal ts = 1.0f / 60.0f;

	//bod_rigid2->enableGravity(false);

	physWorld->update(ts);

	// get updated position of the body
	const reactphysics3d::Transform& transf = bod_rigid->getTransform();
	const reactphysics3d::Vector3 posit = transf.getPosition();
	cube_position_1 = glm::vec3(posit.x, posit.y, posit.z);
	const reactphysics3d::Transform& transf2 = bod_rigid2->getTransform();
	const reactphysics3d::Vector3 posit2 = transf2.getPosition();
	cube_position_2 = glm::vec3(posit2.x, posit2.y, posit2.z);
	const reactphysics3d::Transform& transf3 = bod_rigid3->getTransform();
	const reactphysics3d::Vector3 posit3 = transf3.getPosition();


	

	//const reactphysics3d::Transform& transf4 = bod_rigid4->getTransform();
	//const reactphysics3d::Vector3 posit4 = transf4.getPosition();
	//camera_obj->obj_cam_pos.x = posit4.x;
	//camera_obj->obj_cam_pos.y = posit4.y;
	//camera_obj->obj_cam_pos.z = posit4.z;


	//std::cout << "Position of Rigid Bod: " << posit.x << "," << posit.y << "," << posit.z << std::endl;
	//std::cout << "Position of Rigid Bod 2 : " << posit2.x << "," << posit2.y << "," << posit2.z << std::endl;


}