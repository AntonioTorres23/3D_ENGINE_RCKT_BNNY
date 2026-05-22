#include "process_shadow_map.h"

SHADOW_MAP_OBJ::SHADOW_MAP_OBJ()
{
	glGenFramebuffers(1, &this->depth_map_frame_buffer_object);
}

SHADOW_MAP_OBJ::SHADOW_MAP_OBJ(unsigned int shadow_map_texture_width, unsigned int shadow_map_texture_height)
{

	glGenFramebuffers(1, &this->depth_map_frame_buffer_object);


	std::cout << "Framebuffer Generated" << std::endl;

	this->height_of_texture = shadow_map_texture_width;
	this->width_of_texture = shadow_map_texture_height;
	this->texture_min_filter = GL_NEAREST;
	this->texture_mag_filter = GL_NEAREST;
	this->texture_format_internally = GL_DEPTH_COMPONENT;
	this->texture_format_loaded = GL_DEPTH_COMPONENT; 
	this->texture_wrap_s = GL_REPEAT;
	this->texture_wrap_t = GL_REPEAT;
	this->Initialize_Depth_Map_FBO(shadow_map_texture_width, shadow_map_texture_height);
}

void SHADOW_MAP_OBJ::Initialize_Depth_Map_FBO(unsigned int shadow_map_texture_width, unsigned int shadow_map_texture_height)
{

	// generate a texture object with the address of the stored texture_ID data member within this object
	glGenTextures(1, &this->texture_ID);

	// set the related object data method dimensions equal to the values that are in the arguments


	// create the texture with OpenGL functions
	glBindTexture(GL_TEXTURE_2D, this->texture_ID);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadow_map_texture_width, shadow_map_texture_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	// set the texture parameters with OpenGL functions
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// unbind texture once done creating texture
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, this->texture_ID);
	std::cout << "Shadow Map Created" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, this->depth_map_frame_buffer_object);
	// point depth buffer info to be sent to the previous texture we created
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->texture_ID, 0);
	// tell OpenGL that we do not want to read or draw any color data with this framebuffer object
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	GLint att;

	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &att);

	std::cout << att << std::endl;

	std::cout << "Framebuffer Texture Mapped" << std::endl;


	// unbind depth map buffer object
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	std::cout << this->depth_map_frame_buffer_object << std::endl;
	std::cout << this->texture_ID << std::endl;
	std::cout << shadow_map_texture_width << " " << shadow_map_texture_height << std::endl; 


}