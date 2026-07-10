#include "logic_for_game.h"

class CustomOverlapCallback : public reactphysics3d::OverlapCallback
{
public:

	bool overlap_occured;
	// body that represents the one we want to look for
	reactphysics3d::Body* rigid_body_we_want_to_test;

	CustomOverlapCallback(PHYSICS_OBJ player_arg) : rigid_body_we_want_to_test(player_arg.rigid_body), overlap_occured(false)
	{

	}



	// Override the original function that was stored in the OverlapCallback Class
	virtual void onOverlap(CallbackData& callbackData) override
	{
		// set overlap occurred to false to prevent it from carrying over a false true 
		overlap_occured = false;
		// for loop that iterates through all overlapping pairs within callback data/physics world
		for (unsigned int overlapping_pairs_iterator = 0; overlapping_pairs_iterator < callbackData.getNbOverlappingPairs(); overlapping_pairs_iterator++)
		{
			// grab each individual overlapping body with callback data and overlapping pair index
			reactphysics3d::OverlapCallback::OverlapPair overlapping_pair = callbackData.getOverlappingPair(overlapping_pairs_iterator);

			// grab the first body within the overlapping pair
			reactphysics3d::Body* first_body = overlapping_pair.getBody1();
			// grab the second body within the overlapping pair
			reactphysics3d::Body* second_body = overlapping_pair.getBody2();
			// if first body is the desired body, then the non-desired body is the second body, if not, then the first body is the non-desired body
			reactphysics3d::Body* non_desired_body = (first_body == rigid_body_we_want_to_test) ? second_body : first_body;
			// if the non-desired body is not euqal to the body we want to test, then a overlap has occured, meaning both bodies are not the desired body
			if (non_desired_body != rigid_body_we_want_to_test)
			{
				// overlap has occured
				overlap_occured = true;
				// exit out of the loop early
				return;
			}


		}

	}
};




int key_pressed_counter = 0;
int time_key_can_be_held = 100;

const reactphysics3d::decimal ts = 1.0f / 60.0f;

reactphysics3d::PhysicsCommon physCom;

reactphysics3d::PhysicsWorld* physWorld = physCom.createPhysicsWorld();

//float amount_of_fov = 60.0f; 
float amount_of_fov = 80.0f;

glm::vec3 model_position(-1.0f, 5.0f, 0.0f);

glm::vec3 cube_position_1(-1.0f, 1.0f, 0.0f);

glm::vec3 cube_position_2(0.0f, 1.0f, 0.0f);

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


// CREATE RIDGID BODIES FOR EACH OBJECT WITHIN OUR PHYSICS WORLD

reactphysics3d::Vector3 HalfSpace(1.5, 1.5, 1.5);
reactphysics3d::Vector3 FloorHalfSpace(50.0, 0.0, 50.0);


PHYSICS_OBJ cube1(physCom, physWorld, "BOX", HalfSpace, reactphysics3d::Vector3(cube_position_1.x, cube_position_1.y, cube_position_1.z));
PHYSICS_OBJ cube2(physCom, physWorld, "BOX", HalfSpace, reactphysics3d::Vector3(cube_position_2.x, cube_position_2.y, cube_position_2.z));
PHYSICS_OBJ player(physCom, physWorld, "CAPSULE", 0.6, 0.8, reactphysics3d::Vector3(0.0, 0.0, 0.0));

const int num_of_plane_vertices = 6;

const int num_of_plane_triangles = 2;

float plane_vertices[3 * num_of_plane_vertices] =
{
	   50.0f, -0.5f,  50.0f,
	  -50.0f, -0.5f,  50.0f,
	  -50.0f, -0.5f, -50.0f,

	   50.0f, -0.5f,  50.0f,
	  -50.0f, -0.5f, -50.0f,
	   50.0f, -0.5f, -50.0f
};

unsigned int plane_indices[6] = { 0, 1, 2, 3, 4, 5, };

reactphysics3d::TriangleVertexArray plane_vertex_array = reactphysics3d::TriangleVertexArray(num_of_plane_vertices, plane_vertices, 
	3 * sizeof(float), 2, plane_indices, 3 * sizeof( unsigned int), reactphysics3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE, 
	reactphysics3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

PHYSICS_OBJ floor_test(physCom, physWorld, "CONCAVE_MESH", plane_vertex_array, reactphysics3d::Vector3(floor_position.x, floor_position.y, floor_position.z));

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

	cube1.rigid_body->setType(reactphysics3d::BodyType::DYNAMIC);
	cube2.rigid_body->setType(reactphysics3d::BodyType::DYNAMIC);
	player.rigid_body->setType(reactphysics3d::BodyType::DYNAMIC);
	floor_test.rigid_body->setType(reactphysics3d::BodyType::STATIC);

	player.rigid_body->setLinearDamping(0.5);
	player.rigid_body->setAngularDamping(0.5);


	// THIS AFFECTS A LOT OF THE PHYSICS IN THE WORLD
	//physWorld->setGravity(reactphysics3d::Vector3(0.0, -0.07, 0.0));
	physWorld->setGravity(reactphysics3d::Vector3(0.0, -0.8, 0.0));


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


	render_obj = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), CUBE);
	render_obj_plane = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), PLANE);
	skybox_obj = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("skybox_test"), SKYBOX);

	//model_obj = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/Counter-Terrorists_GIGN/COUNTER-TERRORIST_GIGN.obj", "quad_damage", false);
	model_obj = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/Dust2/Dust2.obj", "quad_damage", false);

	model_obj_2 = new RENDER_OBJECT_OBJ(RESOURCE_MANAGER::Shader_Get("model_test"), MODEL, "assets/Models/B.D. Joe/B.D. Joe.obj", "quad_damage", false);
	
	shadow_map = new SHADOW_MAP_OBJ(1024, 1024);

	camera_obj = new CAM_OBJ(glm::vec3(1.0f, 5.0f, 0.0f));
	
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


	// draw cross hair using im gui library
	auto cross = ImGui::GetBackgroundDrawList();

	cross->AddCircle(ImVec2((this->Width_Of_Screen / 2 ) - 5, (this->Height_Of_Screen / 2)), 25, IM_COL32(0, 255, 0, 255), 100.0f, 1.0f);


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
	{
		if (camera_obj->obj_pitch == -89.0f || camera_obj->obj_pitch == -88.0f)
		{

			camera_obj->obj_cam_pos += camera_obj->obj_cam_front_view * (camera_obj->obj_cam_speed + 1);
			const reactphysics3d::Transform& transf = player.rigid_body->getTransform();
			const reactphysics3d::Vector3 posit = transf.getPosition();

			reactphysics3d::Vector3 temp_vec(camera_obj->obj_cam_pos.x, posit.y, camera_obj->obj_cam_pos.z);
			reactphysics3d::Quaternion temp_quart = reactphysics3d::Quaternion::identity();

			reactphysics3d::Transform temp_trans(temp_vec, temp_quart);

			player.rigid_body->setTransform(temp_trans);
		}


		camera_obj->obj_cam_pos += camera_obj->obj_cam_front_view * camera_obj->obj_cam_speed;
		const reactphysics3d::Transform& transf = player.rigid_body->getTransform();
		const reactphysics3d::Vector3 posit = transf.getPosition();

		reactphysics3d::Vector3 temp_vec(camera_obj->obj_cam_pos.x, posit.y, camera_obj->obj_cam_pos.z);
		reactphysics3d::Quaternion temp_quart = reactphysics3d::Quaternion::identity();

		reactphysics3d::Transform temp_trans(temp_vec, temp_quart);

		player.rigid_body->setTransform(temp_trans);


	}
	if (this->Key_Pressed_Buffer[GLFW_KEY_A])
	{
		camera_obj->obj_cam_pos -= camera_obj->obj_cam_right * camera_obj->obj_cam_speed;
		const reactphysics3d::Transform& transf = player.rigid_body->getTransform();
		const reactphysics3d::Vector3 posit = transf.getPosition();

		reactphysics3d::Vector3 temp_vec(camera_obj->obj_cam_pos.x, posit.y, camera_obj->obj_cam_pos.z);
		reactphysics3d::Quaternion temp_quart = reactphysics3d::Quaternion::identity();

		reactphysics3d::Transform temp_trans(temp_vec, temp_quart);
		player.rigid_body->setTransform(temp_trans);
	}
	if (this->Key_Pressed_Buffer[GLFW_KEY_S])
	{
		camera_obj->obj_cam_pos -= camera_obj->obj_cam_front_view * camera_obj->obj_cam_speed;
		const reactphysics3d::Transform& transf = player.rigid_body->getTransform();
		const reactphysics3d::Vector3 posit = transf.getPosition();

		reactphysics3d::Vector3 temp_vec(camera_obj->obj_cam_pos.x, posit.y, camera_obj->obj_cam_pos.z);
		reactphysics3d::Quaternion temp_quart = reactphysics3d::Quaternion::identity();

		reactphysics3d::Transform temp_trans(temp_vec, temp_quart);

		player.rigid_body->setTransform(temp_trans);


		if (camera_obj->obj_pitch == -89.0f)
		{

			camera_obj->obj_cam_pos -= camera_obj->obj_cam_front_view * (camera_obj->obj_cam_speed + 1);
			
			const reactphysics3d::Vector3 posit = transf.getPosition();
			const reactphysics3d::Transform& transf = player.rigid_body->getTransform();
			reactphysics3d::Vector3 temp_vec(camera_obj->obj_cam_pos.x, posit.y, camera_obj->obj_cam_pos.z);
			reactphysics3d::Quaternion temp_quart = reactphysics3d::Quaternion::identity();

			reactphysics3d::Transform temp_trans(temp_vec, temp_quart);

			player.rigid_body->setTransform(temp_trans);
		}

	}
	if (this->Key_Pressed_Buffer[GLFW_KEY_D])
	{
		camera_obj->obj_cam_pos += camera_obj->obj_cam_right * camera_obj->obj_cam_speed;
		const reactphysics3d::Transform& transf = player.rigid_body->getTransform();
		const reactphysics3d::Vector3 posit = transf.getPosition();

		reactphysics3d::Vector3 temp_vec(camera_obj->obj_cam_pos.x, posit.y, camera_obj->obj_cam_pos.z);
		reactphysics3d::Quaternion temp_quart = reactphysics3d::Quaternion::identity();

		reactphysics3d::Transform temp_trans(temp_vec, temp_quart);

		player.rigid_body->setTransform(temp_trans);
	}
	if (this->Key_Pressed_Buffer[GLFW_KEY_SPACE])
	{
		if (key_pressed_counter < time_key_can_be_held)

		{
			const reactphysics3d::Transform& transf = player.rigid_body->getTransform();
			const reactphysics3d::Vector3 posit = transf.getPosition();

			reactphysics3d::Vector3 temp_vec(posit.x, posit.y + 0.07, posit.z);
			reactphysics3d::Quaternion temp_quart = reactphysics3d::Quaternion::identity();

			reactphysics3d::Transform temp_trans(temp_vec, temp_quart);

			player.rigid_body->setTransform(temp_trans);
			key_pressed_counter++;

		}

	}

	/*
	// CHECKS IF PLAYER HAS LANDED AND THE KEY IS UN-PRESSED: TEST OVERLAP TESTS IF TWO RIDGID BODIES HAS COLLIDED
	if (!this->Key_Pressed_Buffer[GLFW_KEY_SPACE] && physWorld->testOverlap(floor_test.rigid_body, player.rigid_body) || physWorld->testOverlap(player.rigid_body, cube1.rigid_body) || physWorld->testOverlap(player.rigid_body, cube2.rigid_body))
	{
		key_pressed_counter = 0;
	}
	*/

	CustomOverlapCallback overlap_callback(player);

	physWorld->testOverlap(player.rigid_body, overlap_callback);

	if (!this->Key_Pressed_Buffer[GLFW_KEY_SPACE] && overlap_callback.overlap_occured)
	{
		//std::cout << "player has hit ground" << std::endl;

		key_pressed_counter = 0;
	}




	// PROCESS MOUSE BUTTON INPUT
	if (this->Mouse_Button_Pressed_Buffer[GLFW_MOUSE_BUTTON_LEFT])
	{
		std::cout << "BANG!" << std::endl;
	}
	
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

	Mouse_Velocity_Physics(GAME_OBJ::Mouse_Moved);
	

	

}

void GAME_OBJ::Update_Game(float delta_time)
{
	// IF SLIDER IS MOVED; UPDATE CUBE PHYSICS


	if (ImGui::SliderFloat("CUBE 1  X Direction", &cube_position_1.x, -50.0f, 50.0f))
	{
		//const reactphysics3d::Transform& transf = bod_rigid->getTransform();
		const reactphysics3d::Transform& transf = cube1.rigid_body->getTransform();
		
		const reactphysics3d::Vector3 posit = transf.getPosition();
		
		reactphysics3d::Vector3 temp_vec(cube_position_1.x, posit.y, posit.z);
		reactphysics3d::Quaternion temp_quart = reactphysics3d::Quaternion::identity();
		
		reactphysics3d::Transform temp_trans(temp_vec, temp_quart);

		//bod_rigid->setTransform(temp_trans);
		player.rigid_body->setTransform(temp_trans);
	
	}

	if (ImGui::SliderFloat("CUBE 1  Y Direction", &cube_position_1.y, -50.0f, 50.0f))
	{
		//const reactphysics3d::Transform& transf = bod_rigid->getTransform();
		const reactphysics3d::Transform& transf = cube1.rigid_body->getTransform();
		const reactphysics3d::Vector3 posit = transf.getPosition();
		reactphysics3d::Vector3 temp_vec(posit.x, cube_position_1.y, posit.z);
		reactphysics3d::Quaternion temp_quart = reactphysics3d::Quaternion::identity();

		reactphysics3d::Transform temp_trans(temp_vec, temp_quart);

		//bod_rigid->setTransform(temp_trans);
		player.rigid_body->setTransform(temp_trans);
		
	}

	if (ImGui::SliderFloat("CUBE 1  Z Direction", &cube_position_1.z, -50.0f, 50.0f))
	{
		//const reactphysics3d::Transform& transf = bod_rigid->getTransform();
		const reactphysics3d::Transform& transf = cube1.rigid_body->getTransform();
		const reactphysics3d::Vector3 posit = transf.getPosition();

		reactphysics3d::Vector3 temp_vec(posit.x, posit.y, cube_position_1.z);
		reactphysics3d::Quaternion temp_quart = reactphysics3d::Quaternion::identity();

		reactphysics3d::Transform temp_trans(temp_vec, temp_quart);

		//bod_rigid->setTransform(temp_trans);
		player.rigid_body->setTransform(temp_trans);
	}

	GAME_OBJ::Process_User_Input(delta_time);


	// USE THIS TO PREVENT THE PHYSICS ENGINE FROM GIVING TOO MUCH "BOUNCINESS" WITHIN ITS PHYSICS SIM

	if (physWorld->testOverlap(floor_test.rigid_body, player.rigid_body))
	{
		//std::cout << "player on floor" << std::endl;
		player.rigid_body->setLinearVelocity(reactphysics3d::Vector3(0.0, 0.0, 0.0));
		player.rigid_body->setAngularVelocity(reactphysics3d::Vector3(0.0, 0.0, 0.0));

	
	}
	if (!physWorld->testOverlap(floor_test.rigid_body, player.rigid_body))
	{
		//std::cout << "player not on floor" << std::endl;
	}
	

	Mouse_Velocity_Physics(GAME_OBJ::Mouse_Moved);

	// update physics world
	physWorld->update(ts);

	
	// get updated position of the body
	const reactphysics3d::Transform& transf = cube1.rigid_body->getTransform();
	const reactphysics3d::Vector3 posit = transf.getPosition();
	cube_position_1 = glm::vec3(posit.x, posit.y, posit.z);
	
	const reactphysics3d::Transform& transf2 = cube2.rigid_body->getTransform();
	const reactphysics3d::Vector3 posit2 = transf2.getPosition();
	cube_position_2 = glm::vec3(posit2.x, posit2.y, posit2.z);
	
	const reactphysics3d::Transform& transf4 = player.rigid_body->getTransform();
	const reactphysics3d::Vector3 posit4 = transf4.getPosition();
	camera_obj->obj_cam_pos.x = posit4.x;
	camera_obj->obj_cam_pos.y = posit4.y;
	camera_obj->obj_cam_pos.z = posit4.z;


}

// CURRENTLY TESTING FUNCTION
void GAME_OBJ::Mouse_Velocity_Physics(bool mouse_moved_argument)
{
	
	if (mouse_moved_argument)
	{ 

		if (this->Key_Pressed_Buffer[GLFW_KEY_SPACE] && this->Key_Pressed_Buffer[GLFW_KEY_W] && this->Key_Pressed_Buffer[GLFW_KEY_A])
		{

			if (key_pressed_counter < time_key_can_be_held)
			{
				player.rigid_body->applyLocalForceAtCenterOfMass(reactphysics3d::Vector3(camera_obj->obj_cam_front_view.x * 7, 0.0, camera_obj->obj_cam_front_view.z * 7));
			
			}
		}

		if (this->Key_Pressed_Buffer[GLFW_KEY_SPACE] && this->Key_Pressed_Buffer[GLFW_KEY_W] && this->Key_Pressed_Buffer[GLFW_KEY_D])
		{
			if (key_pressed_counter < time_key_can_be_held)
			{
				
				player.rigid_body->applyLocalForceAtCenterOfMass(reactphysics3d::Vector3(camera_obj->obj_cam_front_view.x * 7, 0.0, camera_obj->obj_cam_front_view.z * 7));
			}
		}
	}

	/*
	if (!this->Key_Pressed_Buffer[GLFW_KEY_SPACE] && this->Key_Pressed_Buffer[GLFW_KEY_W] && this->Key_Pressed_Buffer[GLFW_KEY_D] && physWorld->testOverlap(floor_test.rigid_body, player.rigid_body))
	{
		key_pressed_counter = 0;

	}


	if (!this->Key_Pressed_Buffer[GLFW_KEY_SPACE] && this->Key_Pressed_Buffer[GLFW_KEY_W] && this->Key_Pressed_Buffer[GLFW_KEY_A] && physWorld->testOverlap(floor_test.rigid_body, player.rigid_body))
	{
		key_pressed_counter = 0;

	}
	*/

	CustomOverlapCallback overlap_callback(player);

	physWorld->testOverlap(player.rigid_body, overlap_callback);

	if (!this->Key_Pressed_Buffer[GLFW_KEY_SPACE] && this->Key_Pressed_Buffer[GLFW_KEY_W] && this->Key_Pressed_Buffer[GLFW_KEY_D] && overlap_callback.overlap_occured)
	{
		key_pressed_counter = 0;

	}

	if (!this->Key_Pressed_Buffer[GLFW_KEY_SPACE] && this->Key_Pressed_Buffer[GLFW_KEY_W] && this->Key_Pressed_Buffer[GLFW_KEY_A] && overlap_callback.overlap_occured)
	{
		key_pressed_counter = 0;

	}




}