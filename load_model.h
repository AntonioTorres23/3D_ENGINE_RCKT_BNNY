#ifndef LOAD_MODEL_HEADER
#define LOAD_MODEL_HEADER	

#include "resource_manager.h"

#include "load_mesh.h" // include load_mesh header file to get access to the MESH_OBJ class template

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp> // allows us to transform matrixes with this like scaling, translating, etc

#include "stb_image.h" // the file that loads and processes textures of multiple file types into a format that OpenGL can read

#include <assimp/Importer.hpp> // open asset importer library that allows us to proccess a scene that takes in multiple 3D model file types: for example .obj, .sae, etc

#include <assimp/scene.h> // allows us to load scenes from the model file types

#include <assimp/postprocess.h>

#include <string>

#include <fstream>

#include <sstream>

#include <iostream>

#include <map>

#include <vector>

// prototype for processing textures from the directory that the model files are in
unsigned int Textures_In_Model_Directory(const char* texture_file_path, const std::string& model_files_directory, bool gamma = false);


// create a model class

class MODEL_OBJ
{
public:
	// create a vector method of the tData type to store the vertex data gathered from the model file
	std::vector<tData_Struct> tex_already_loaded; // a vector that stores all of the texture files that are already loaded
	// create a vector member of the MESH_OBJ class type to store the meshes that we have processed
	std::vector<MESH_OBJ> model_meshes;
	// create a string member that stores the directory name where the model data is stored
	std::string model_files_directory;
	// create a bool member that stores the gama correction option for textures
	bool gammaCor;

	MODEL_OBJ() {};

	// the constructor of our class which takes in a path the model data filetype as well as enabling the member gammaCorrection prior to the code runnning in the bracket of our constructor, we are setting the results to false in the constructor arguments
	MODEL_OBJ(std::string path_to_3D_model_filetype, std::string model_name, bool gam = false);

private:
	// private function that loads the 3D model with a library called assimp
	void Model_Load(std::string path_to_3D_model_filetype, std::string model_path_name);

	// process/parse through the object's nodes and retrieve the data that is within
	// this function is recursive meaning it will call itself until all of the data within is processed
	void Parse_Node(aiNode* model_node, const aiScene* model_scene);

	// function that takes the MESH_OBJ data type and goes through and processes all the data within
	MESH_OBJ Parse_Mesh(aiMesh* model_mesh, const aiScene* model_scene);

	// Load_Textures_From_Materials is a private function that checks all material textures of a type (i.e. diffuse, specular, normal) and loads them if they already haven't been loaded yet
	// all of the information is then returned as a tData_Struct
	// takes a std::vector of our tData_Struct
	// takes in 3 arguments: an pointer with the the aiMaterial datatype, an aiTexture type, and a string that specifies the type with our previous naming convention
	std::vector<tData_Struct> Load_Textures_From_Materials(aiMaterial* model_material, aiTextureType tex_type, std::string tex_type_name);
};

#endif // !LOAD_MODEL_HEADER

