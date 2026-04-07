#version 330 core

layout (location = 0) in vec3 local_coordinates; 
layout (location = 1) in vec2 texture_coordiantes; 
layout (location = 2) in vec3 raw_normal_coordinates;

out vec2 tex_coords;
out vec3 position_of_model_fragments;
out vec3 normal_coordinates;

uniform mat4 transformation_matrix;
uniform mat4 view_matrix;
uniform mat4 perspective_matrix;
uniform mat3 normal_coordinates_transformation_matrix;



void main()
{
	tex_coords = texture_coordiantes;

	// calculating the model's fragment position in world space by multiplying the original vector_position_coordinates by the transformation_matrix
	position_of_model_fragments = vec3(transformation_matrix * vec4(local_coordinates, 1.0));

	// we have to multiply the normal coordinates with the transformation matrix to be able to use it for our lighting calculations
	normal_coordinates = normal_coordinates_transformation_matrix * raw_normal_coordinates;

	gl_Position = perspective_matrix * view_matrix * transformation_matrix * vec4(local_coordinates, 1.0);
	
}