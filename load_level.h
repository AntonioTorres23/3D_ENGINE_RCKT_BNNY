#ifndef LOAD_LEVEL_HEADER
#define LOAD_LEVEL_HEADER
#include "physics_object.h"
#include "resource_manager.h"
#include "render_object.h"

class LOAD_LEVEL
{
public:

	static void level_load(const char* path_to_level_file);
};

#endif // !LOAD_LEVEL_HEADER
