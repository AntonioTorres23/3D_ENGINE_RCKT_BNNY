#include "LIGHTING_UNIFORMS.h"

LIGHTING_UNIFORMS::LIGHTING_UNIFORMS(const SHADER_OBJ& shader_object_argument)
{
	this->shader_obj;
}


void LIGHTING_UNIFORMS::Configure_Directional_Lighting(std::string name_of_directional_lighting_obj, glm::vec3 camera_world_position, glm::vec3 light_direction, glm::vec3 ambient_color, glm::vec3 diffuse_color, glm::vec3 specular_color)
{
	
	this->shader_obj.Activate();

	std::string directional_lighting_direction_struct_data_member = name_of_directional_lighting_obj + ".light_direction";

	std::string directional_lighting_ambient_struct_data_member = name_of_directional_lighting_obj + ".ambient_color";

	std::string directional_lighting_diffuse_struct_data_member = name_of_directional_lighting_obj + ".diffuse_color";

	std::string directional_lighting_specular_struct_data_member = name_of_directional_lighting_obj + ".specular_color";

	this->shader_obj.uniform_vector_3(directional_lighting_direction_struct_data_member.c_str(), light_direction);

	this->shader_obj.uniform_vector_3(directional_lighting_ambient_struct_data_member.c_str(), ambient_color);

	this->shader_obj.uniform_vector_3(directional_lighting_diffuse_struct_data_member.c_str(), diffuse_color);

	this->shader_obj.uniform_vector_3(directional_lighting_specular_struct_data_member.c_str(), specular_color);

	this->shader_obj.uniform_vector_3("camera_world_position", camera_world_position);

}