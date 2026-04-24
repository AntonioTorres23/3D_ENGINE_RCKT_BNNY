#ifndef LOAD_MESH_HEADER

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include <vector>
#include <string>

#define MAX_BONE_INFLUENCE_DATA 4 // sets the max number of data from bone indexes which are primarily used for animation data

// create a vertex structure that will hold the vertex data gathered from the model
struct vData_Struct 
{
	// vertex_position_coordinates
	glm::vec3 vertex_position_coordinates;
	// vertex_normal_coordinates
	glm::vec3 vertex_normal_coordinates;
	// vertex_texture_coordinates
	glm::vec2 vertex_texture_coordinates;
	// vertex_tangent_coordinates
	glm::vec3 vertex_tangent_coordinates;
	// vertex_bi-tangent_coordinates
	glm::vec3 vertex_bi_tangent_coordinates;
	// vertex_bone_indexes
	int vertex_bone_indexes[MAX_BONE_INFLUENCE_DATA];
	// weight of each bone which means how much pull it has in moving the vertices that it influences
	float vertex_bone_weights[MAX_BONE_INFLUENCE_DATA];
};

// create a texture structure that will hold the texture data gathered from the model
// think of uv textures and stuff like that
struct tData_Struct 
{
	// texture ID for OpenGL
	unsigned int texID;
	// string to help with parsing through the texture type
	std::string tex_type;
	// path to texture 
	std::string tex_path;
};







#endif // !LOAD_MESH_HEADER
