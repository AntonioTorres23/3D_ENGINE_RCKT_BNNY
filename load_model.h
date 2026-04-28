#ifndef LOAD_MODEL_HEADER

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

// create a model class

class MODEL_OBJ
{
public:
	// create a vector member of the MESH_OBJ class type to store the meshes that we have processed
	std::vector<MESH_OBJ> model_meshes;
	// create a string member that stores the directory name where the model data is stored
	std::string model_files_directory;
	// create a bool member that stores the gama correction option for textures
	bool gammaCor;

	// the constructor of our class which takes in a path the model data filetype as well as enabling the member gammaCorrection prior to the code runnning in the bracket of our constructor, we are setting the results to false in the constructor arguments
	MODEL_OBJ(std::string path_to_3D_model_filetype, std::string model_name, bool gam = false) : gammaCor(gam)
	{
		// object loads the model data once the Model_OBJ object is created
		Model_Load(path_to_3D_model_filetype, model_name);
	}
private:
	// private function that loads the 3D model with a library called assimp
	void Model_Load(std::string path_to_3D_model_filetype, std::string model_path_name)
	{
		// create a varible/object from assimp that imports 3D models
		Assimp::Importer model_importer;
		// generate a scene which contains the root of all the data in a 3D model file; you call the function ReadFile from the model importer var/object and enter the path along with the options you want to add when the 3D model gets imported into the a scene
		const aiScene* model_scene = model_importer.ReadFile(path_to_3D_model_filetype, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		// check if scene doesn't get generated
		// remember we use the -> when we have a pointer and we want to call methods/functions that are within that pointer, its the equivelent to *. 
		if (!model_scene || model_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !model_scene->mRootNode)
		{
			std::cout << "ERROR::OPEN_ASSET_IMPORTER_(ASSIMP)_::" << model_importer.GetErrorString();
			// return and basically stop the rest of the function here if there is an error
			return;
		}
		// get the directory name of where all the model files/textures are at and store it in that public method that we defined prior
		model_files_directory = path_to_3D_model_filetype.substr(0, path_to_3D_model_filetype.find_last_of('/'));
		RESOURCE_MANAGER::Store_Model_Path_Load(model_files_directory.c_str(), model_path_name);
		// process the model's nodes that are located within the node of the model object's scene
		Parse_Node(model_scene->mRootNode, model_scene);

	}

	// process/parse through the object's nodes and retrieve the data that is within
	// this function is recursive meaning it will call itself until all of the data within is processed
	void Parse_Node(aiNode* model_node, const aiScene* model_scene)
	{
		// process all of the meshes that are located within the current node
		for (unsigned int mesh = 0; mesh < model_node->mNumMeshes; mesh++)
		{
			// the node obj only has indices to index the actual objects within the scene
			// the scene contains all the mesh data, the node is just there for organization (such as the relation between nodes)
			// so the scene has all the mesh data so we use a this pointer to grab that in addition to the node this pointer within the index of the meshes stored in an array or something similar to get the location
			aiMesh* meshes = model_scene->mMeshes[model_node->mMeshes[mesh]];
			// now push this data into the model_meshes member vector
			// we use the meshes aiMesh variable as well as the model scene from the argument from the parse node function for the Parse_Mesh function
			model_meshes.push_back(Parse_Mesh(meshes, model_scene));

		}

		// after all meshes are processed, processes all of the children nodes within the root node and recursively check for meshes and addiontal nodes in there until there are none left
		for (unsigned int cNode = 0; cNode < model_node->mNumChildren; cNode++)
		{
			// recursivley parse all of the children nodes and see if they have any data within until there are no child nodes left
			Parse_Node(model_node->mChildren[cNode], model_scene);
		}
	}

	// function that takes the MESH_OBJ data type and goes through and processes all the data within
	MESH_OBJ Parse_Mesh(aiMesh* model_mesh, const aiScene* model_scene)
	{
		// create vectors of the previous structs that we created in the Mesh class header file
		std::vector<vData_Struct> mesh_vData;
		std::vector<unsigned int> mesh_iData;
		std::vector<tData_Struct> mesh_tData;

		// go through each of the vertex data located within the mesh
		for (unsigned int vertices = 0; vertices < model_mesh->mNumVertices; vertices++)
		{

			// our place holder struct that holds all the different vertex data and pushes it to the official vertex data struct vector mesh_vData at the end
			// remember that this is only a single structure, not a vector of structures like mesh_vData 
			vData_Struct placeholder_vector_struct;
			// create a seperate 3 coordinate vector
			// placeholder vector to store the vertex data from assimp here
			glm::vec3 placeholder_vector;
			placeholder_vector.x = model_mesh->mVertices[vertices].x;
			placeholder_vector.y = model_mesh->mVertices[vertices].y;
			placeholder_vector.z = model_mesh->mVertices[vertices].z;


			placeholder_vector_struct.vertex_position_coordinates = placeholder_vector; // add our placeholder vector positional data to the glm::vec3 vertex_position_coordinates variable stored within the structure

			// now check if model_mesh has normal vertices
			if (model_mesh->HasNormals())
			{
				// overwrite your position data coordinates with the normal data coordinates using the same vector place_holder_vector
				placeholder_vector.x = model_mesh->mNormals[vertices].x;
				placeholder_vector.y = model_mesh->mNormals[vertices].y;
				placeholder_vector.z = model_mesh->mNormals[vertices].z;
				placeholder_vector_struct.vertex_normal_coordinates = placeholder_vector; // add our placeholder vector normal data to the glm::vec3 vertex_normal_coordinates variable stored within the structure 
			}
			// now check if model_mesh has texture coordinates
			if (model_mesh->mTextureCoords[0])
			{
				// create a new placeholder vector of 2 since texture coordinates only have that many vertices
				glm::vec2 placeholder_texture_vector;

				// a vertex can contain up to 8 different texture coordinates; we then make the assumption to not use models where a vertex can have multiple texture coordinates so always take the first set (index 0)
				placeholder_texture_vector.x = model_mesh->mTextureCoords[0][vertices].x;
				placeholder_texture_vector.y = model_mesh->mTextureCoords[0][vertices].y;

				placeholder_vector_struct.vertex_texture_coordinates = placeholder_texture_vector;

				if (model_mesh->HasTangentsAndBitangents())
				{

					// use the original place holder vector for the tangents
					placeholder_vector.x = model_mesh->mTangents[vertices].x;
					placeholder_vector.y = model_mesh->mTangents[vertices].y;
					placeholder_vector.z = model_mesh->mTangents[vertices].z;


					placeholder_vector_struct.vertex_tangent_coordinates = placeholder_vector;

					// use the original place holder vector for the bi tangents as well
					placeholder_vector.x = model_mesh->mBitangents[vertices].x;
					placeholder_vector.y = model_mesh->mBitangents[vertices].y;
					placeholder_vector.z = model_mesh->mBitangents[vertices].z;

					placeholder_vector_struct.vertex_bi_tangent_coordinates = placeholder_vector;
				}

			}
			else
				// if there are no texture coordinates set the texture coordinates to a vector of 2 with location (0.0, 0.0)
				placeholder_vector_struct.vertex_texture_coordinates = glm::vec2(0.0f, 0.0f);

			// push the placeholder_vector_struct to the mesh_vData vector that holds vData_structs
			mesh_vData.push_back(placeholder_vector_struct);
		}
		// parse through each of the mesh's faces (a face is a mesh's triangle) and get the corresponding vertex indices
		for (unsigned int face = 0; face < model_mesh->mNumFaces; face++)
		{
			// create a variable with the aiFace data type that stores the amount of faces within the model that is loaded
			aiFace model_face = model_mesh->mFaces[face];
			// nested for loop that goes through the each face, grabs the indices, and puts them into 
			for (unsigned int indices = 0; indices < model_face.mNumIndices; indices++)
				// push into the vector mesh_iData that stores unsigned ints for all the indices in each of the model's faces
				mesh_iData.push_back(model_face.mIndices[indices]);
		}

		// process the materials within the models directory which are the textures 

		// create a pointer variable of the aiMaterial data type and assign it to the data mMaterials which is found in the scene
		aiMaterial* model_material = model_scene->mMaterials[model_mesh->mMaterialIndex];
		// we create a naming convention for each different textuer type within the shaders

		// check the mesh class to get more info on our naming conventions

		// diffuse: diffTex

		// specular: specTex

		// normal: normTex

		// height: heightTex

		// create a vector with the tData_Struct type that will store our diffuseMaps
		// we run the function Load_Textures_From_Materials and store the return placeholder_texture_vector in the diffMaps vector
		// for the args we use the model_material pointer, aiTextureTypeDiffuse enumeration type, as well as a string with our naming convention for our shaders 
		std::vector<tData_Struct> diffMaps = Load_Textures_From_Materials(model_material, aiTextureType_DIFFUSE, "diffTex");
		// within the mesh_tData vector, insert the diffMaps vector data with the C++ built in function insert
		// we will start with ending the inital data within textures, then, we will begin adding the diffMaps vector into the mesh_tData vector, then end the insertion of the diffMaps vector
		mesh_tData.insert(mesh_tData.end(), diffMaps.begin(), diffMaps.end());

		// create a vector for the specular maps
		std::vector<tData_Struct> specMaps = Load_Textures_From_Materials(model_material, aiTextureType_SPECULAR, "specTex");
		// add the specMaps to the mesh_tData vector using the built-in C++ function insert
		mesh_tData.insert(mesh_tData.end(), specMaps.begin(), specMaps.end());

		// create a vector for the normal maps
		std::vector<tData_Struct> normMaps = Load_Textures_From_Materials(model_material, aiTextureType_NORMALS, "normTex");
		// add the normMaps to the mesh_tData vector usinggg the built-in C++ function insert
		mesh_tData.insert(mesh_tData.end(), normMaps.begin(), normMaps.end());

		// create a vector for the height maps
		std::vector<tData_Struct> heightMaps = Load_Textures_From_Materials(model_material, aiTextureType_HEIGHT, "heightTex");
		// add the heightMaps to the to the mesh_tData vector using built-in C++ function insert
		mesh_tData.insert(mesh_tData.end(), heightMaps.begin(), heightMaps.end());

		// return a mesh object with the constructor values being the data we've gathered from this Parse_Mesh function
		return MESH_OBJ(mesh_vData, mesh_iData, mesh_tData);

	}

};



#endif // !LOAD_MODEL_HEADER

