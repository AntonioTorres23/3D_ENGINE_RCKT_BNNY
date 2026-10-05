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
		// take string stream and in a while loop grab each line by using the built in function std::getline to grab the file info line by line and store it in levelString
		while (std::getline(levelSTRINGSTREAM, levelString))
		{
			size_t location = levelString.find(":");
			std::string location_string = levelString.substr(location + 1);
			if (location_string.find("(") != std::string::npos)
			{
				std::vector<int> coordinates;
				glm::vec3 vector;
				for (char character : location_string)
				{
					if (character >= '0' && character <= '9')
					{
						// convert digital character to an integer
						int vector_coordinate = character - '0';
						coordinates.push_back(vector_coordinate);
					}
				}
				
				vector.x = coordinates[0];
				vector.y = coordinates[1];
				vector.z = coordinates[2];

				reactphysics3d::Vector3 world_position(vector.x, vector.y, vector.z);


				for (int x = 0; x < 3; x++)
				{
					std::cout << coordinates[x] << std::endl;
				}
			}

			if (location_string.find("cube") != std::string::npos)
			{
				std::cout << location_string << std::endl; 
			}

			if (location_string.find("sphere") != std::string::npos)
			{
				std::cout << location_string << std::endl;
			}

			if (location_string.find("capsule") != std::string::npos)
			{
				std::cout << location_string << std::endl;
			}

			if (location_string.find("assets/Models/") != std::string::npos)
			{
				std::cout << location_string << std::endl;
			}

			if (location_string.find("shaders/") != std::string::npos)
			{
				std::cout << location_string << std::endl;
			}

		}

		
		
	}
	// if there is an error, catch it here and thrown a custom exception statment that we send to default output with c out
	catch (std::exception load_level_file_error)
	{
		std::cout << "ERROR::LEVEL_FILES::FAILED_TO_READ_LEVEL_FILE(S)" << std::endl;
	}
	
	
}