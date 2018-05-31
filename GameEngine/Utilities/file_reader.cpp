#include "file_reader.h"
#include <fstream>

bool FileReader::readFile(const char * fileName, std::string &readedFile)
{
	//opening file for reading
	FILE* file;

	if (fopen_s(&file, fileName, "r"))
	{
		return false;
	}

	//getting length of the file
	fseek(file, 0, SEEK_END);
	unsigned long length = ftell(file);
	
	//+ 1 for '/0' char
	char* data = new char[length + 1];
	memset(data, 0, length + 1);

	//reading from file
	fseek(file, 0, SEEK_SET);
	fread_s(data, length + 1, sizeof(char), length, file);
	fclose(file);
	
	//craeting string with file content
	readedFile.append(data);

	//freeing memory
	delete[] data;
	return true;
}
