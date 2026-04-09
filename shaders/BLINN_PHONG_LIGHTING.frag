#version 330 core


// DirectionLighting Structure to hold all the data of the global direction light
// think of the directional light as "world light"; it mimics lighting such as the sun
struct DirectionalLighting
{
	vec3 light_direction;

	vec3 ambient_color;

	vec3 diffuse_color;

	vec3 specular_color;
};




in vec2 tex_coords;
in vec3 position_of_model_fragments;
in vec3 normal_coordinates;

out vec4 color_output;

uniform sampler2D texture_image;
uniform vec3 camera_world_position;
uniform DirectionalLighting directional_lighting_obj;

vec3 DirectionalLightingCalculations (DirectionalLighting direction_lighting_arg, vec3 normal_coordinates_arg, vec3 pos_of_camera_arg);

void main()
{
	vec3 normalized_normal_coordiantes = normalize(normal_coordinates);

	vec3 normalized_direction_of_camera_from_the_model = normalize(camera_world_position - position_of_model_fragments);

	vec3 lighting_calculations = DirectionalLightingCalculations(directional_lighting_obj, normalized_normal_coordiantes, normalized_direction_of_camera_from_the_model);
	
	//vec3 tex = texture(texture_image, tex_coords).rgb;
	color_output = vec4(lighting_calculations, 1.0);
}


vec3 DirectionalLightingCalculations (DirectionalLighting direction_lighting_arg, vec3 normal_coordinates_arg, vec3 pos_of_camera_arg)
{
	// we only negate the light direction since directional lighting affects everything in the environment
	vec3 light_direction = normalize(-direction_lighting_arg.light_direction);

	// calculations for diffuse_lighting
	vec3 diffuse_lighting = vec3(max(dot(normal_coordinates_arg, light_direction), 0.0));


	// halfway direction between camera_world_position and light_direction for specular_lighting
	vec3 halfway_direction = normalize(light_direction + pos_of_camera_arg);
	
	// we only need the position of the camera and the direction of reflection since there is no "distance" between the light pos and the model/obj(s)
	float specular_lighting = pow(max(dot(pos_of_camera_arg, halfway_direction), 0.0), 32);

	vec3 ambient_return = direction_lighting_arg.ambient_color * vec3(texture(texture_image, tex_coords).rgb);

	vec3 diffuse_return = direction_lighting_arg.diffuse_color * diffuse_lighting * vec3(texture(texture_image, tex_coords).rgb);

	vec3 specular_return = direction_lighting_arg.specular_color * specular_lighting * vec3(texture(texture_image, tex_coords).rgb);

	//return (ambient_lighting + diffuse_lighting + specular_lighting);
	return (ambient_return + diffuse_return + specular_return);
}

