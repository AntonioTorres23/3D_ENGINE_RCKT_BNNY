#version 330 core

layout (location = 0) in vec3 local_coordinates; 
layout (location = 1) in vec2 texture_coordiantes; 

out vec2 tex_coords;

uniform mat4 transformation_matrix;
uniform mat4 view_matrix;
uniform mat4 perspective_matrix;

void main()
{
	gl_Position = perspective_matrix * view_matrix * transformation_matrix * vec4(local_coordinates, 1.0);
	tex_coords = texture_coordiantes;
}