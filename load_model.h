#ifndef LOAD_MODEL_HEADER

#include <glad/glad.h>

#include <glm/glm.hpp> // our library

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

class Model_OBJ
{

};



#endif // !LOAD_MODEL_HEADER

