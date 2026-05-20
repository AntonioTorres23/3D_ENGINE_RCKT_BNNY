#include "process_shadow_map.h"

SHADOW_MAP_OBJ::SHADOW_MAP_OBJ()
{
	glGenFramebuffers(1, &this->depth_map_frame_buffer_object);
}

SHADOW_MAP_OBJ::SHADOW_MAP_OBJ(unsigned int shadow_map_texture_width, unsigned int shadow_map_texture_height)
{
	glGenFramebuffers(1, &this->depth_map_frame_buffer_object);
	this->height_of_texture = shadow_map_texture_width;
	this->width_of_texture = shadow_map_texture_height;
	this->texture_min_filter = GL_NEAREST;
	this->texture_mag_filter = GL_NEAREST;
	this->texture_format_internally = GL_DEPTH_COMPONENT;
	this->texture_format_internally = GL_DEPTH_COMPONENT; 
	this->texture_wrap_s = GL_CLAMP_TO_EDGE;
	this->texture_wrap_t = GL_CLAMP_TO_EDGE;
	this->Initialize_Depth_Map_FBO(shadow_map_texture_width, shadow_map_texture_height);
}

void SHADOW_MAP_OBJ::Initialize_Depth_Map_FBO(unsigned int shadow_map_texture_width, unsigned int shadow_map_texture_height)
{
	
	this->Create_Texture(shadow_map_texture_height, shadow_map_texture_width, nullptr);

	glBindFramebuffer(GL_FRAMEBUFFER, this->depth_map_frame_buffer_object);
	// point depth buffer info to be sent to the previous texture we created
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->texture_ID, 0);
	// tell OpenGL that we do not want to read or draw any color data with this framebuffer object
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	// unbind depth map buffer object
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


}