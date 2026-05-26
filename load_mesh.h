#ifndef LOAD_MESH_HEADER
#define LOAD_MESH_HEADER

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

class MESH_OBJ
{
public:
	// create a public vector member (standard library version) that stores vData structs
	// be sure to specify the data type you want to store in the vector prior to the method/variable name
	std::vector<vData_Struct> model_vData;
	// create a public member vector that stores only the indices grabbed from the model data
	std::vector<unsigned int> iData;
	// create a public vector member that stores tData structs
	std::vector<tData_Struct> model_tData;
	// create a public vertex array object member
	unsigned int Vertex_Array_Object;

	// constructor to specify arguements in order to create a Model_Mesh object as well as run certain code upon the creation of the object
	MESH_OBJ(std::vector<vData_Struct> arg_model_vData, std::vector<unsigned int> arg_model_iData, std::vector<tData_Struct> arg_model_tData);

private:
	// private methods that create our VBO and EBO
	unsigned int Vertex_Buffer_Object, Element_Buffer_Object;

	// private function that sets up the vertex buffer object data and the vertex array object pointers, same applies for the element buffer object
	void Build_Mesh();
};

#endif