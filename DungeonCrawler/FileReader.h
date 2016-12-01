#pragma once

#include <iostream>
#include <fstream>

class FileReader
{
public:
	static FileReader &getInstance();
	vector<string> * ReadFile(string, bool = false);

private:
	FileReader();
	FileReader(FileReader const&);
	void operator=(FileReader const&);
};

