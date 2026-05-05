#include "load_model.h"


// Textures_In_Model_Directory is a function that takes the textures that are within the model's directory and loads them into a OpenGL format with stb_image
// It also sets the repeat and filtering options of the textures as well

unsigned int Textures_In_Model_Directory(const char* texture_file_path, const std::string& model_files_directory, bool gamma)
{

	// convert texture_file_path into a string
	std::string name_of_texture_file = std::string(texture_file_path);

	// concat the directory that the texture files are located in along with a / and then the name of the texture file
	name_of_texture_file = model_files_directory + "/" + name_of_texture_file;

	RESOURCE_MANAGER::Texture_Load(name_of_texture_file.c_str(), gamma, model_files_directory);

	return RESOURCE_MANAGER::Texture_Get(model_files_directory).texture_ID;
	/*
	// create an unsigned int for a texture ID
	unsigned int texID;
	// generate a texture object using glGenTextures, we only want to create one object and provide the address of our texture ID
	glGenTextures(1, &texID);
	// provide the width, height, and ammount of RGB components
	int w, h, amount_of_RGB_components;

	// load texture with name_of_texture_file converted to a c-string as well as the addresses of the width, height and amount of RGB components
	unsigned char* tex_data = stbi_load(name_of_texture_file.c_str(), &w, &h, &amount_of_RGB_components, 0);

	// if there is texture data loaded from stbi_load, run this block of code
	if (tex_data)
	{
		// Create a GLenum variable that takes the amount of color components that where gathered prior from the tex_data pointer and assign it to an enumeration that matches the color components gathered
		GLenum tex_col_format;
		if (amount_of_RGB_components == 1)
			tex_col_format = GL_RED;
		if (amount_of_RGB_components == 3)
			tex_col_format = GL_RGB;
		if (amount_of_RGB_components == 4)
			tex_col_format = GL_RGBA;

		// bind the texture object to the GL_TEXTURE_2D type enumeration
		glBindTexture(GL_TEXTURE_2D, texID);
		// enter the configuration you want within the glfw function glTexImaage 2D
		glTexImage2D(GL_TEXTURE_2D, 0, tex_col_format, w, h, 0, tex_col_format, GL_UNSIGNED_BYTE, tex_data);
		// generate a mipmap with this glfw function
		glGenerateMipmap(GL_TEXTURE_2D);
		// add our wrapping and filtering options on the current texture object

		// texture wrapping options for the s coordinates
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // S is our X for texture coordinates
		// texture wrapping options for the t coordinates
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // T is our Y for texture coordinates
		// set filtering options for minimum (for textures on objects that are further away)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // for the min texture filter, use the mipmap that was generated as well as the linear filtering method
		// set filtering options for magnification (for textures on objects that are closer)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // for the mag texture filter, use only the linear filtering method, no mipmap

		// free the previous image data with this stb image function for the next texture object
		stbi_image_free(tex_data);

	}
	// if you cannot load texture data from path, send ERROR MESSAGE to default output and free the texture data with stbi_image_free
	else
	{
		std::cout << "ERROR::CANNOT_LOAD_TEXTURE_AT_PATH: " << texture_file_path << std::endl;

		stbi_image_free(tex_data);
	}

	return texID;
	*/
}