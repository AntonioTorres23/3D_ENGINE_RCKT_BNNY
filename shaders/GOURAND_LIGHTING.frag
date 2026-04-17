#version 330 core

in vec3 ambient_return;
in vec3 diffuse_return;
in vec3 specular_return; 
in vec2 tex_coords;

out vec4 display_fragments;

uniform sampler2D texture_image;

void main()
{
	vec3 ambient = ambient_return * texture(texture_image, tex_coords).rgb;
	vec3 diffuse = diffuse_return * texture(texture_image, tex_coords).rgb;
	vec3 specular = specular_return * texture(texture_image, tex_coords).rgb;
	 

	display_fragments = vec4((ambient + diffuse + specular), 1.0);	
	//display_fragments = vec4(1.0, 1.0, 0.0, 1.0);

}

