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
	
	glm::mat4 transformation_matrix = glm::mat4(1.0f);

	transformation_matrix = glm::translate(transformation_matrix, position_of_object_argument);

	transformation_matrix = glm::scale(transformation_matrix, scale_size_argument);

	transformation_matrix = glm::rotate(transformation_matrix, glm::radians(rotation_degree_argument), glm::vec3(0.0f, 1.0f, 0.0f));

	//glm::mat4 view_matrix = glm::lookAt(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//glm::mat4 perspective_matrix = glm::perspective(glm::radians(90.0f), (float)800 / (float)1000, 0.1f, 100.0f);


	object_shader_obj.uniform_matrix_4("transformation_matrix", transformation_matrix);

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
		std::cout << "plane drawn" << std::endl;
		break;


	case CUBE:
		glDrawArrays(GL_TRIANGLES, 0, amount_of_triangles_to_draw_cube); 
		glBindVertexArray(0);
		break;

	default:
		std::cout << "NOT A COMPATIBLE OBJECT" << std::endl;
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	
		std::cout << "CUBE SETUP COMPLETE" << std::endl;

		break;
	
	default:
		std::cout << "COULD NOT SETUP OBJ" << std::endl; 
	}
}

