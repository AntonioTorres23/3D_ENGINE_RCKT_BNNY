#ifndef PROCESS_SHADOW_MAP_HEADER
#define PROCESS_SHADOW_MAP_HEADER
#include "process_texture.h"

class SHADOW_MAP_OBJ : public TEXTURE_2D_OBJ
{
public:

	SHADOW_MAP_OBJ();

	SHADOW_MAP_OBJ(unsigned int shadow_map_texture_width, unsigned int shadow_map_texture_height);

	unsigned int depth_map_frame_buffer_object;

private:

	void Initialize_Depth_Map_FBO(unsigned int shadow_map_texture_width, unsigned int shadow_map_texture_height);

};

#endif // !PROCESS_SHADOW_MAP_HEADER
