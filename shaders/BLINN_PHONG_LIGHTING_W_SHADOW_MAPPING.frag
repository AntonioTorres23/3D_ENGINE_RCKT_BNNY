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


float Calculate_Shadows(vec4 light_space_model_fragments);

in vec2 tex_coords;
in vec3 position_of_model_fragments;
in vec3 normal_coordinates;
in vec4 position_of_model_fragments_from_light_pov;

out vec4 color_output;


uniform sampler2D diffTex1;
uniform sampler2D shadowDepthMapTexture;
uniform vec3 camera_world_position;
uniform DirectionalLighting directional_lighting_obj;

vec3 DirectionalLightingCalculations (DirectionalLighting direction_lighting_arg, vec3 normal_coordinates_arg, vec3 pos_of_camera_arg);

void main()
{
	vec3 normalized_normal_coordiantes = normalize(normal_coordinates);

	vec3 normalized_direction_of_camera_from_the_model = normalize(camera_world_position - position_of_model_fragments);

	vec3 lighting_calculations = DirectionalLightingCalculations(directional_lighting_obj, normalized_normal_coordiantes, normalized_direction_of_camera_from_the_model);
	
	//vec3 tex = texture(texture_image, tex_coords).rgb;
	//color_output = vec4(lighting_calculations, 1.0);

	color_output = vec4(lighting_calculations, 1.0);
}


vec3 DirectionalLightingCalculations (DirectionalLighting direction_lighting_arg, vec3 normal_coordinates_arg, vec3 pos_of_camera_arg)
{


	// we only negate the light direction since directional lighting affects everything in the environment
	vec3 light_direction = normalize(-direction_lighting_arg.light_direction);

	// calculations for diffuse_lighting
	float diffuse_lighting = max(dot(light_direction, normal_coordinates_arg), 0.0);

	// halfway direction between camera_world_position and light_direction for specular_lighting
	vec3 halfway_direction = normalize(light_direction + pos_of_camera_arg);
	
	// we only need the position of the camera and the direction of reflection since there is no "distance" between the light pos and the model/obj(s)
	float specular_lighting = pow(max(dot(normal_coordinates_arg, halfway_direction), 0.0), 32);

	vec3 ambient_return = direction_lighting_arg.ambient_color * vec3(texture(diffTex1, tex_coords).rgb);

	vec3 diffuse_return = direction_lighting_arg.diffuse_color * diffuse_lighting * vec3(texture(diffTex1, tex_coords).rgb);

	vec3 specular_return = direction_lighting_arg.specular_color * specular_lighting * vec3(texture(diffTex1, tex_coords).rgb);

	// use calculate shadows function to see if current fragment is in shadow or not
	float in_shadow = Calculate_Shadows(position_of_model_fragments_from_light_pov);

	//return (ambient_lighting + diffuse_lighting + specular_lighting);
	
	// we add the ambient_return by the 1.0 - shadow (inverse) to determine how much the fragment isn't in shadow
	return (ambient_return + (1.0 - in_shadow) * (diffuse_return + specular_return));
}


float Calculate_Shadows(vec4 light_space_model_fragments)
{
	// do perspective division on the light space coordinates by dividing xyz by the homogenous coordinate w
	// (since this is an orthographic matrix, we don't need to do this but we will do it anyways in case we switch to a perspective matrix))
	// this returns a light-space position that is in the range of -1 to 1
	vec3 light_space_projection_coordinates = light_space_model_fragments.xyz / light_space_model_fragments.w;

	// transform the range of light_space_projection_coordinates to Normalized Device Coordinates range (0 to 1)
	// we do this by first multiplying it by 0.5 and then adding it by 0.5
	light_space_projection_coordinates = light_space_projection_coordinates * 0.5 + 0.5;

	// now we take the NDC projection_coordiantes's xy values and use them to for the shadow depth map's texture coordinates
	// this gives the closest dpeth from the light's pov
	// I know it's weird but think of this as the x and y are right in front of the light since we are using
	// no z value in this case, there's no depth yet
	float closest_depth_value = texture(shadowDepthMapTexture, light_space_projection_coordinates.xy).r;

	// now we seperate our z coordinate from light_space_projection_coordinates to represent the current depth of a fragment from the light's pov
	float current_depth_value_from_light_perspective = light_space_projection_coordinates.z;


	// now compare if current fragment is in shadow; if the current depth value is higher than the closest depth value, the fragment is in shadow (1.0) else, its not (0.0)
	float in_shadow = current_depth_value_from_light_perspective > closest_depth_value ? 1.0 : 0.0;

	// return in shadow as our return value
	return in_shadow;


}