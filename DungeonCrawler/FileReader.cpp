#include "stdafx.h"
#include "FileReader.h"

FileReader::FileReader()
{
}

FileReader & FileReader::getInstance()
{
	static FileReader instance;
	return instance;
}

vector<string> * FileReader::ReadFile(string path, bool onlyReadBrackets = false)
{
	vector<string> * lines;
	string line;
	std::ifstream myfile(path);
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			if(!onlyReadBrackets || line[1] == '[')
				lines->push_back(line);
		}
		myfile.close();
	}

	else ConsoleWriter::getInstance().WriteLine(new vector<string>{ "A ERROR OCCURED READING FILE IN LOCATION:", path });

	return lines;
}
