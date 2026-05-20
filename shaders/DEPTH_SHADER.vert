#version 330 core

layout (location = 0) in vec3 local_coordinates; 

uniform mat4 transformation_matrix;
uniform mat4 light_matrix_for_shadow_mapping;

void main()
{

	gl_Position = light_matrix_for_shadow_mapping * transformation_matrix * vec4(local_coordinates, 1.0);

}
