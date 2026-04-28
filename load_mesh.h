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
	MESH_OBJ(std::vector<vData_Struct> arg_model_vData, std::vector<unsigned int> arg_model_iData, std::vector<tData_Struct> arg_model_tData)
	{
		// assign whatever data is gathered from the 3 arguments in the constructor to thier respective public methods stored within the class
		model_vData = arg_model_vData;

		iData = arg_model_iData;

		model_tData = arg_model_tData;

		// after gathering all the required data, begin setting up our VBO, EBO, and attribute pointers

		Build_Mesh();


	}
private:
	// private methods that create our VBO and EBO
	unsigned int Vertex_Buffer_Object, Element_Buffer_Object;

	// private function that sets up the vertex buffer object data and the vertex array object pointers, same applies for the element buffer object
	void Build_Mesh()
	{
		// generate the VBO, VAO, and EBO
		glGenVertexArrays(1, &Vertex_Array_Object);
		glGenBuffers(1, &Vertex_Buffer_Object);
		glGenBuffers(1, &Element_Buffer_Object);

		// bind the VAO
		glBindVertexArray(Vertex_Array_Object);
		// bind VBO to allow vertex data to be loaded
		glBindBuffer(GL_ARRAY_BUFFER, Vertex_Buffer_Object);
		// structure's memory layout is sequential (which means it stays in order at all times) for all its data within
		// passing a pointer of the model_vData fits the formatting of a glm::vec array perfectly
		glBufferData(GL_ARRAY_BUFFER, model_vData.size() * sizeof(vData_Struct), &model_vData[0], GL_STATIC_DRAW);

		// bind EBO to allow index data to be loaded
		// make sure for the buffer to use GL_ELEMENT_ARRAY_BUFFER since it's indices rather than vertices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Element_Buffer_Object);
		// similar structure to the VBO data we loaded prior
		// except remember to include GL_ELEMENT_ARRAY_BUFFER as your first parameter rather than GL_ARRAY_BUFFER since we are working with indices
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, iData.size() * sizeof(unsigned int), &iData[0], GL_STATIC_DRAW);

		// begin adding the attribute pointers for the different kinds of vertex data that we will be using
		// the vertex data for positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vData_Struct), (void*)0);
		// the vertex data for normal coordinates
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vData_Struct), (void*)offsetof(vData_Struct, vertex_normal_coordinates));
		// the vertex data for texture coordinates
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vData_Struct), (void*)offsetof(vData_Struct, vertex_texture_coordinates));
		// the vertex data for tangent coordinates
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vData_Struct), (void*)offsetof(vData_Struct, vertex_tangent_coordinates));
		// the vertex data for bi-tangent coordinates
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vData_Struct), (void*)offsetof(vData_Struct, vertex_bi_tangent_coordinates));
		// the vertex data for bone indexes
		glEnableVertexAttribArray(5);
		// use the OpenGL function glVertexAttribIPointer because we are using integers as our data
		glVertexAttribIPointer(5, 4, GL_INT, sizeof(vData_Struct), (void*)offsetof(vData_Struct, vertex_bone_indexes));
		// the vertex data for bone weights
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(vData_Struct), (void*)offsetof(vData_Struct, vertex_bone_weights));
		glBindVertexArray(0);
	}

};





#endif // !LOAD_MESH_HEADER

