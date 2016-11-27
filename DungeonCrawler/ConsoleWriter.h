#pragma once

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class ConsoleWriter
{
	public:
		static ConsoleWriter &getInstance();
		void WriteLine(const string&);
		void WriteLine(const vector<string>*);
		void ClearView();

	private:
		ConsoleWriter();
		ConsoleWriter(ConsoleWriter const&);
		void operator=(ConsoleWriter const&);
};

