#version 330 core
/*
// DirectionLighting Structure to hold all the data of the global direction light
// think of the directional light as "world light"; it mimics lighting such as the sun
struct DirectionalLighting
{
	vec3 light_direction;

	vec3 ambient_color;

	vec3 diffuse_color;

	vec3 specular_color;
};
*/

layout (location = 0) in vec3 local_coordinates; 
layout (location = 1) in vec3 raw_normal_coordinates;
layout (location = 2) in vec2 texture_coordiantes; 

/*
out vec3 ambient_return;
out vec3 diffuse_return;
out vec3 specular_return; 
out vec2 tex_coords;
*/

uniform mat4 transformation_matrix;
uniform mat4 view_matrix;
uniform mat4 perspective_matrix;
uniform mat3 normal_coordinates_transformation_matrix;
//uniform vec3 camera_world_position;
//uniform DirectionalLighting directional_lighting_obj;


//out vec3 tex_coords

void main()
{
	
	// do gl_Position calculations first for gourand shading
	gl_Position = perspective_matrix * view_matrix * transformation_matrix * vec4(local_coordinates, 1.0);

	/*
	tex_coords = texture_coordiantes;

	// calculating the model's fragment position in world space by multiplying the original vector_position_coordinates by the transformation_matrix
	position_of_model_fragments = vec3(transformation_matrix * vec4(local_coordinates, 1.0));

	// we have to multiply the normal coordinates with the transformation matrix to be able to use it for our lighting calculations
	normal_coordinates = normal_coordinates_transformation_matrix * raw_normal_coordinates;

	vec3 normalized_normal_coordiantes = normalize(normal_coordinates);

	vec3 normalized_direction_of_camera_from_the_model = normalize(camera_world_position - position_of_model_fragments);

	// we only negate the light direction since directional lighting affects everything in the environment
	vec3 light_direction = normalize(-directional_lighting_obj.light_direction);

	// calculations for diffuse_lighting
	float diffuse_lighting = max(dot(light_direction, normalized_normal_coordiantes), 0.0);

	// halfway direction between camera_world_position and light_direction for specular_lighting
	vec3 halfway_direction = normalize(light_direction + normalized_direction_of_camera_from_the_model);
	
	// we only need the position of the camera and the halfway direction since there is no "distance" between the light pos and the model/obj(s)
	float specular_lighting = pow(max(dot(normalized_normal_coordiantes, halfway_direction), 0.0), 32);

	ambient_return = directional_lighting_obj.ambient_color;

	diffuse_return = directional_lighting_obj.diffuse_color * diffuse_lighting;

	specular_return = directional_lighting_obj.specular_color * specular_lighting;
	*/
}