#ifndef PROCESS_CUBEMAP_TEXTURE_HEADER
#define PROCESS_CUBEMAP_TEXTURE_HEADER

#include <glad/glad.h> // include glad for OpenGL pointer functions 

#include <vector>

#include "GLENUM_CUBEMAP_TEXTURE_POSITIONS.h"

/*
enum SKY_BOX_TEXTURE_POSITIONS
{
	POS_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X, NEG_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X, POS_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y, NEG_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, POS_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z, NEG_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};
*/

/*
std::vector<GLenum> extern sky_box_tex_positions =
{
	GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};
*/

//  can store and set parameters of a CUBEMAP Texture; Along with function for utility
class CUBEMAP_TEXTURE_OBJ
{
public: // where all publicly accessible methods/functions go

	// method that stores texture ID 
	unsigned int texture_ID;
	// stores the dimensions of the 2D texture; width and height
	unsigned int width_of_texture, height_of_texture;
	// format of texture internally (i.e. GL_RED, GL_RG, GL_RGB)
	unsigned int texture_format_internally;
	// format of the already loaded image within OpenGL
	unsigned int texture_format_loaded;
	// texture parameters
	// methods for storing texture's s, t, and r (x, y and z) parameters
	unsigned int texture_wrap_s;
	unsigned int texture_wrap_t;
	unsigned int texture_wrap_r;
	// methods for storing texture's min and mag filter parameters
	unsigned int texture_min_filter;
	unsigned int texture_mag_filter;
	// constructor for this class/object which sets default texture modes
	CUBEMAP_TEXTURE_OBJ();
	// prototype function definition that generates a texture from the image data provided
	void Create_Texture(unsigned int texture_w, unsigned int texture_h, unsigned char* texture_data, GLenum sky_box_texture_position);
	// binds current texture as an active GL_TEXTURE_2D object
	void Bind_Texture() const; // defined as a const function to deny it permission to change the values of data value member within the texture class
};

#endif // !PROCESS_CUBEMAP_TEXTURE_HEADER

