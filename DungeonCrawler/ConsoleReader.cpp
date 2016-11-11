#include "stdafx.h"
#include "ConsoleReader.h"


ConsoleReader::ConsoleReader()
{
}

ConsoleReader & ConsoleReader::getInstance()
{
	static ConsoleReader instance;
	return instance;
}
