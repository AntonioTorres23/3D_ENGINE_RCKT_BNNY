#version 330 core

in vec2 tex_coords;

out vec4 color_output;

uniform sampler2D texture_image;

void main()
{
	vec3 tex = texture(texture_image, tex_coords).rgb;
	color_output = vec4(tex, 1.0);
}