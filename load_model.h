#ifndef LOAD_MODEL_HEADER

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include "stb_image.h"

#include <assimp/Importer.hpp>

#include <assimp/scene.h>

#include <assimp/postprocess.h>

#include "prep_mesh.h"

#include "process_shader.h"

#include <string>

#include "process_texture.h"

//#include <fstream>

//#include <sstream>

#include "resource_manager.h"

TEXTURE_2D_OBJ Load_Model_Textures(const char* texture_file_path);





#endif // !LOAD_MODEL_HEADER

