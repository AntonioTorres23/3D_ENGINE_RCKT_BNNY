#include "render_object.h" // include header file to access class template

/*
NOTICE HOW WE'RE DEFINING THE FUNCTIONS THAT ARE STORED WITHIN THE RENDER_SPRITE_OBJ CLASS/OBJECT, SO IN THE C++ FILE HERE WE'RE DEFINING THE ACTUAL SOURCE CODE
THE FUNCTIONS THAT ARE STORED IN THE HEADER FILE ARE REALLY ONLY PROTOTYPES
*/

RENDER_OBJECT_OBJ::RENDER_OBJECT_OBJ(const SHADER_OBJ& shader_object_argument, Object_Type type_of_object)
{
	this->Type_Of_Object = type_of_object; 
	this->object_shader_obj = shader_object_argument;

	this->vertex_data_intialize(type_of_object);

}

RENDER_OBJECT_OBJ::~RENDER_OBJECT_OBJ()
{
	glDeleteVertexArrays(1, &this->object_vertex_array_obj);
	glDeleteBuffers(1, &this->object_element_array_obj);
}

