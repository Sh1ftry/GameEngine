#pragma once
#include <string>

/*
*	@breif Class responsible for handling file reading
*/
class FileReader
{
public:
	/*
	*	@brief Reads file
	*	@param[in] filePath Path to file
	*	@param[out] readedFile Readed file
	*/
	static bool readFile(const char* filePath, std::string& readedFile);
};