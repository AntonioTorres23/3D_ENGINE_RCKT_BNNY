#ifndef LIGHTING_UNIFORMS_HEADER
#define LIGHTING_UNIFORMS_HEADER

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

#include "process_shader.h"

// LIGHTING_UNIFORMS class template
/*
uses static functions which is a function that belongs to a class iteslf rather than an object itself;
meaning that you can call the function with LIGHTING_UNIFORMS::FUNCTION rather than having to assign an object to that class
i.e. LIGHTING_UNIFORMS object; object.function()
in addition to this static functions only have access to other static data members or functions
*/
class LIGHTING_UNIFORMS
{
public:

	LIGHTING_UNIFORMS(const SHADER_OBJ& shader_object_argument);
	
	void Configure_Directional_Lighting(std::string name_of_directional_lighting_obj, glm::vec3 camera_world_position, glm::vec3 light_direction = glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3 ambient_color = glm::vec3(1.0f), glm::vec3 diffuse_color = glm::vec3(1.0f), glm::vec3 specular_color = glm::vec3(1.0f));

private:
	SHADER_OBJ shader_obj;
};


#endif // !LIGHTING_UNIFORMS_HEADER
