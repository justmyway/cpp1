#include "stdafx.h"
#include <iostream>

#include "ConsoleReader.h"

ConsoleReader::ConsoleReader()
{
}

ConsoleReader & ConsoleReader::getInstance()
{
	static ConsoleReader instance;
	return instance;
}

string ConsoleReader::ReadLine() {
	string str;
	std::getline(std::cin, str);
	return str;
}