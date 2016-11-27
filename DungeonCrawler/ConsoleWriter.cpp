#include "stdafx.h"
#include "ConsoleWriter.h"


ConsoleWriter::ConsoleWriter()
{
}

ConsoleWriter & ConsoleWriter::getInstance()
{
	static ConsoleWriter instance;
	return instance;
}

void ConsoleWriter::WriteLine(const string & line) {
	cout << line << endl;
}

void ConsoleWriter::WriteLine(const vector<string>* multipleLines)
{
	for (auto line : *multipleLines)
		WriteLine(line);

	delete multipleLines;
}

void ConsoleWriter::ClearView()
{
	system("cls");
}
