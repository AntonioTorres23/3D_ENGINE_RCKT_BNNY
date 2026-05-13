#include "render_object.h" // include header file to access class template


/*
NOTICE HOW WE'RE DEFINING THE FUNCTIONS THAT ARE STORED WITHIN THE RENDER_OBJECT_OBJ CLASS/OBJECT, SO IN THE C++ FILE HERE WE'RE DEFINING THE ACTUAL SOURCE CODE
THE FUNCTIONS THAT ARE STORED IN THE HEADER FILE ARE REALLY ONLY PROTOTYPES
*/

// define contructor for RENDER_OBJECT_OBJ
// CHANGE ON 1/14/2026 @ 2:45 PM, CHANGED CONSTRUCTOR PARAMTER/ARGUMENT OF RENDER_OBJECT_OBJ FROM A SHADER_OBJ &SHADER_OBJECT_ARGUMENT TO A CONST SHADER_OBJ &SHADER_OBJECT_ARGUMENT 
RENDER_OBJECT_OBJ::RENDER_OBJECT_OBJ(const SHADER_OBJ& shader_object_argument, Object_Type type_of_object)
{
	this->Type_Of_Object = type_of_object; 
	this->object_shader_obj = shader_object_argument;

	this->vertex_data_intialize(type_of_object);

}

RENDER_OBJECT_OBJ::RENDER_OBJECT_OBJ(const SHADER_OBJ& shader_object_argument, Object_Type type_of_object, std::string path_to_3D_model_filetype, std::string model_name, bool gamma)
{
	this->Type_Of_Object = type_of_object; 
	this->object_shader_obj = shader_object_argument;

	this->vertex_data_intialize(type_of_object, path_to_3D_model_filetype, model_name, gamma);
}


// define deconstructor for RENDER_SPRITE_OBJ
RENDER_OBJECT_OBJ::~RENDER_OBJECT_OBJ()
{
	// within the body of the deconstructor, delete the vertex array object private data member that we where using to store our sprite vertex data
	glDeleteVertexArrays(1, &this->object_vertex_array_obj);
	//glDeleteBuffers(1, &this->object_element_array_obj);
}

// CHANGE ON 1/14/2026 @ 4:30 PM, CHANGED PARAMTER/ARGUMENT OF RENDER_AND_DRAW_OBJECT METHOD FUNCTION FROM A TEXTURE_2D_OBJ &TEXTURE_2D_OBJECT_ARGUMENT TO A CONST TEXTURE_2D_OBJ &TEXTURE_2D_OBJECT_ARGGUMENT 
void RENDER_OBJECT_OBJ::Render_and_Draw_Object(const TEXTURE_2D_OBJ& texture_object_argument, glm::vec3 position_of_object_argument, glm::vec3 scale_size_argument, float rotation_degree_argument, glm::vec3 object_color_argument)
{
	this->object_shader_obj.Activate();
	
	this->transformation_matrix = glm::mat4(1.0f);

	transformation_matrix = glm::translate(transformation_matrix, position_of_object_argument);

	transformation_matrix = glm::scale(transformation_matrix, scale_size_argument);

	transformation_matrix = glm::rotate(transformation_matrix, glm::radians(rotation_degree_argument), glm::vec3(0.0f, 1.0f, 0.0f));

	// GLM MAT3 MATRIX THAT IS FOR THE NORMAL COORDINATES WHICH IS THE INVERSED TRANSPOSED MATRIX OF OUR TRANSFORMATION MATRIX
	// WE MAKE IT A 3X3 TO LOSE ITS TRANSLATION PROPERTIES
	glm::mat3 normal_coordinates_transformation_matrix = glm::mat3(1.0f);

	normal_coordinates_transformation_matrix = glm::transpose(glm::inverse(transformation_matrix));


	//glm::mat4 view_matrix = glm::lookAt(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//glm::mat4 perspective_matrix = glm::perspective(glm::radians(90.0f), (float)800 / (float)1000, 0.1f, 100.0f);


	object_shader_obj.uniform_matrix_4("transformation_matrix", transformation_matrix);

	object_shader_obj.uniform_matrix_3("normal_coordinates_transformation_matrix", normal_coordinates_transformation_matrix);

	//object_shader_obj.uniform_matrix_4("view_matrix", view_matrix);

	//object_shader_obj.uniform_matrix_4("perspective_matrix", perspective_matrix);


	glActiveTexture(GL_TEXTURE0);
	texture_object_argument.Bind_Texture();
	glBindVertexArray(this->object_vertex_array_obj);
	switch (this->Type_Of_Object)
	{
	case PLANE:
		glDrawArrays(GL_TRIANGLES, 0, amount_of_triangles_to_draw_plane);
		glBindVertexArray(0);
		break;


	case CUBE:
		glDrawArrays(GL_TRIANGLES, 0, amount_of_triangles_to_draw_cube); 
		glBindVertexArray(0);
		break;

	case SKYBOX:
		glDrawArrays(GL_TRIANGLES, 0, amount_of_triangles_to_draw_skybox);
		glBindVertexArray(0);
		break;

	default:
		std::cout << "NOT A COMPATIBLE OBJECT" << std::endl;
	}

	
}

// CHANGE ON 1/14/2026 @ 4:30 PM, CHANGED PARAMTER/ARGUMENT OF RENDER_AND_DRAW_OBJECT METHOD FUNCTION FROM A TEXTURE_2D_OBJ &TEXTURE_2D_OBJECT_ARGUMENT TO A CONST TEXTURE_2D_OBJ &TEXTURE_2D_OBJECT_ARGGUMENT 
void RENDER_OBJECT_OBJ::Render_and_Draw_Object(const CUBEMAP_TEXTURE_OBJ& texture_object_argument)
{
	this->object_shader_obj.Activate();

	glActiveTexture(GL_TEXTURE0);
	texture_object_argument.Bind_Texture();
	glBindVertexArray(this->object_vertex_array_obj);
	switch (this->Type_Of_Object)
	{
	case SKYBOX:
		glDrawArrays(GL_TRIANGLES, 0, amount_of_triangles_to_draw_skybox);
		glBindVertexArray(0);
		break;

	default:
		std::cout << "NOT A COMPATIBLE OBJECT" << std::endl;
	}
}


void RENDER_OBJECT_OBJ::Render_and_Draw_Object(glm::vec3 position_of_object_argument, glm::vec3 scale_size_argument, float rotation_degree_argument, glm::vec3 object_color_argument)
{
	this->object_shader_obj.Activate();

	this->transformation_matrix = glm::mat4(1.0f);

	transformation_matrix = glm::translate(transformation_matrix, position_of_object_argument);

	transformation_matrix = glm::scale(transformation_matrix, scale_size_argument);

	transformation_matrix = glm::rotate(transformation_matrix, glm::radians(rotation_degree_argument), glm::vec3(0.0f, 1.0f, 0.0f));

	// GLM MAT3 MATRIX THAT IS FOR THE NORMAL COORDINATES WHICH IS THE INVERSED TRANSPOSED MATRIX OF OUR TRANSFORMATION MATRIX
	// WE MAKE IT A 3X3 TO LOSE ITS TRANSLATION PROPERTIES
	glm::mat3 normal_coordinates_transformation_matrix = glm::mat3(1.0f);

	normal_coordinates_transformation_matrix = glm::transpose(glm::inverse(transformation_matrix));


	object_shader_obj.uniform_matrix_4("transformation_matrix", transformation_matrix);

	object_shader_obj.uniform_matrix_3("normal_coordinates_transformation_matrix", normal_coordinates_transformation_matrix);


	// create an unsigned int variable to represent the ammount of diffuse textures
	unsigned int number_of_diffuse_textures = 1;
	// create an unsigned int variable to represent the ammount of specular textures 
	unsigned int number_of_specular_textures = 1;
	// create an unsigned int variable to represent the ammount of normal textures
	unsigned int number_of_normal_textures = 1;
	// create an unsigned int variable to represent the amount of height textures
	unsigned int number_of_height_textures = 1;
	
	

	for (unsigned int mesh = 0; mesh < this->model_obj_priv.model_meshes.size(); mesh++)
	{

		// parse through the size of the model_tData vector and activate the amount of textures gathered from the size
		for (unsigned int for_loop_texture_size_integer = 0; for_loop_texture_size_integer < this->model_obj_priv.model_meshes.size(); for_loop_texture_size_integer++)
		{
			// remember that the GL_TEXTURE has a data type of GLenum which is esentially an unsigned integer so we can loop through that as well as add to GL_TEXTURE0 to increase it to GL_TEXTURE1 and so on
			glActiveTexture(GL_TEXTURE0 + for_loop_texture_size_integer);
			// create a string that holds the current number of whatever texture type you are on, think of it as the diffTex1, or specTex3
			std::string texNum;
			// create another string called texName to store the name of whatever the texture type is called, like diffTex, or specTex, or normTex
			// this was one of the variables that we have stored within this tData structure which is also a string
			std::string texName = model_obj_priv.model_meshes[mesh].model_tData[for_loop_texture_size_integer].tex_type;
			// if texName is equal to diffTex convert the unsigned integer number of number_of_diffuse_textures to a string that gets sent to texNum and incremented at the same time 
			if (texName == "diffTex")
				texNum = std::to_string(number_of_diffuse_textures++);
			// if texName is equal to specTex convert the unsigned integer of number_of_specular_textures to a string that gets sent to texNum and incremented at the same time
			else if (texName == "specTex")
				texNum = std::to_string(number_of_specular_textures++);
			// if texName is equal to normTex convert the unsigned integer number of number_of_normal_textures to a string that gets sent to texNum and incremented at the same time
			else if (texName == "normTex")
				texNum = std::to_string(number_of_normal_textures++);
			// if texName is equal to heightTex convert the unsigned integer number of number_of_height_textures to a string that gets sent to texNum and incremented at the same time
			else if (texName == "heightTex")
				texNum = std::to_string(number_of_height_textures++);

			//std::cout << "for loop size integer" << for_loop_texture_size_integer << std::endl;
			//std::cout << "texture id" << model_obj_priv.model_meshes[mesh].model_tData[for_loop_texture_size_integer].texID << std::endl;

			// set the uniform 1 integer function of the integer for loop variable we provided and concatenate texName and texNumber to find the location of the shader type in the shader program we just found within our if-else statments
			// remember we are setting wherever the texture is located in the shader program ID and setting the for loop integer as its new value in the shaders
			glUniform1i(glGetUniformLocation(this->object_shader_obj.Shader_ID, (texName + texNum).c_str()), for_loop_texture_size_integer);
			// then bind the current for_loop_texture integer with GL_TEXTURE_2D
			glBindTexture(GL_TEXTURE_2D, model_obj_priv.model_meshes[mesh].model_tData[for_loop_texture_size_integer].texID);

			

		}



		glBindVertexArray(model_obj_priv.model_meshes[mesh].Vertex_Array_Object);
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(model_obj_priv.model_meshes[mesh].iData.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}
}

// define the void private member function vertex_data_initalize

void RENDER_OBJECT_OBJ::vertex_data_intialize(Object_Type type_of_object)
{
	


	switch (type_of_object)
	{
	case PLANE:
		unsigned int plane_vertex_buffer_object; 

		glGenVertexArrays(1, &this->object_vertex_array_obj);
		glGenBuffers(1, &plane_vertex_buffer_object);
		glBindBuffer(GL_ARRAY_BUFFER, plane_vertex_buffer_object);
		glBufferData(GL_ARRAY_BUFFER, size_of_plane_vertex_data, &plane_vertex_data, GL_STATIC_DRAW);
		glBindVertexArray(this->object_vertex_array_obj);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		std::cout << "PLANE SETUP COMPLETE" << std::endl; 
		
		break;

	case CUBE:
		unsigned int cube_vertex_buffer_object;

		glGenVertexArrays(1, &this->object_vertex_array_obj);
		glGenBuffers(1, &cube_vertex_buffer_object);
		glBindBuffer(GL_ARRAY_BUFFER, cube_vertex_buffer_object);
		glBufferData(GL_ARRAY_BUFFER, size_of_cube_vertex_data, &cube_vertex_data, GL_STATIC_DRAW);
		glBindVertexArray(this->object_vertex_array_obj);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	
		std::cout << "CUBE SETUP COMPLETE" << std::endl;

		break;

	case SKYBOX:		
		unsigned int skybox_cube_vertex_buffer_object;

		glGenVertexArrays(1, &this->object_vertex_array_obj);
		glGenBuffers(1, &skybox_cube_vertex_buffer_object);
		glBindBuffer(GL_ARRAY_BUFFER, skybox_cube_vertex_buffer_object);
		glBufferData(GL_ARRAY_BUFFER, size_of_skybox_vertex_data, &skybox_cube_vertex_data, GL_STATIC_DRAW);
		glBindVertexArray(this->object_vertex_array_obj);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindVertexArray(0);

		std::cout << "SKYBOX SETUP COMPLETE" << std::endl;

		break;


	
	default:
		std::cout << "COULD NOT SETUP OBJ" << std::endl; 
	}

}

void RENDER_OBJECT_OBJ::vertex_data_intialize(Object_Type type_of_object, std::string path_to_3D_model_filetype, std::string name_for_model, bool gamma)
{
	switch (type_of_object)
	{
	case MODEL:
		this->model_obj_priv = MODEL_OBJ(path_to_3D_model_filetype, name_for_model, gamma);
		std::cout << "MODEL SETUP COMPLETE" << std::endl;
	}

	
}

