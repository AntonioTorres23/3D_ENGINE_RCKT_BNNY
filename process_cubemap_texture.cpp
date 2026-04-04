#include <iostream> // include iostream to send default output

#include "process_cubemap_texture.h" // include header file to access class template

/*
NOTICE HOW WE'RE DEFINING THE FUNCTIONS THAT ARE STORED WITHIN THE TEXTURE_2D_OBJ CLASS/OBJECT, SO IN THE C++ FILE HERE WE'RE DEFINING THE ACTUAL SOURCE CODE
THE FUNCTIONS THAT ARE STORED IN THE HEADER FILE ARE REALLY ONLY PROTOTYPES
*/

// define constructor with constructor intalizer list containing relevant values to set data members
CUBEMAP_TEXTURE_OBJ::CUBEMAP_TEXTURE_OBJ() : width_of_texture(0), height_of_texture(0), texture_format_internally(GL_RGB), texture_format_loaded(GL_RGB), texture_wrap_s(GL_CLAMP_TO_EDGE), texture_wrap_t(GL_CLAMP_TO_EDGE), texture_wrap_r(GL_CLAMP_TO_EDGE), texture_min_filter(GL_LINEAR), texture_mag_filter(GL_LINEAR)
{
	// generate a texture object with the address of the stored texture_ID data member within this object
	glGenTextures(1, &this->texture_ID);
}

// define create_texture member function
void CUBEMAP_TEXTURE_OBJ::Create_Texture(unsigned int texture_w, unsigned int texture_h, unsigned char* texture_data, GLenum sky_box_texture_position)
{
	// set the related object data method dimensions equal to the values that are in the arguments
	this->width_of_texture = texture_w;
	this->height_of_texture = texture_h;

	// create the texture with OpenGL functions
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture_ID);
	glTexImage2D(sky_box_texture_position, 0, this->texture_format_internally, texture_w, texture_h, 0, this->texture_format_loaded, GL_UNSIGNED_BYTE, texture_data);
	// set the texture parameters with OpenGL functions
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_CLAMP_TO_EDGE, this->texture_wrap_s);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_CLAMP_TO_EDGE, this->texture_wrap_t);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_CLAMP_TO_EDGE, this->texture_wrap_r);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, this->texture_min_filter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, this->texture_mag_filter);
	// unbind texture once done creating texture
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

// define bind_texture member function; remember we make it constant so that it doesn't effect the data member values within the texture class
void CUBEMAP_TEXTURE_OBJ::Bind_Texture() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture_ID);
}