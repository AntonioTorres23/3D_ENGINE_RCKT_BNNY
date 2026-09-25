#include "load_level.h"
#include <iostream> // include iostream to send default output to the terminal
#include <sstream> // include sstream to import all of the raw source code fstream into a string stream
#include <fstream> // include fstream to read external files and put them in a read buffer
#include <filesystem> // include filesystem to find files in a certain directory

void LOAD_LEVEL::level_load(const char* path_to_level_file)
{
	// create string variables that are used to store the source code from the string stream
	std::string levelString;

	// try statment to attempt opening and reading the source code from the level file paths
	try
	{
		// try to open the level files with ifstream
		std::ifstream levelIFSTREAM(path_to_level_file);
		// create string stream
		std::stringstream levelSTRINGSTREAM;
		// use the string streams and try to read the ifstream buffers into the string streams
		// you use the rdbuf method function to achieve this
		levelSTRINGSTREAM << levelIFSTREAM.rdbuf();
		// now we close the IFSTREAM shader variables
		levelIFSTREAM.close();
		// convert string stream into a regular string and store this within the string variable we created eariler in this function
		levelString = levelSTRINGSTREAM.str();

		std::cout << "\n" << "\n" << levelString << "\n" << "\n" << std::endl;
		
	}
	// if there is an error, catch it here and thrown a custom exception statment that we send to default output with c out
	catch (std::exception load_level_file_error)
	{
		std::cout << "ERROR::LEVEL_FILES::FAILED_TO_READ_LEVEL_FILE(S)" << std::endl;
	}
	
	
}