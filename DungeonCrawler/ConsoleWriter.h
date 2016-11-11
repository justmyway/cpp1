#pragma once

#include <iostream>

using std::cout;
using std::endl;
using std::string;

class ConsoleWriter
{
	public:
		static ConsoleWriter &getInstance();
		void WriteLine(const string&);

	private:
		ConsoleWriter();
		ConsoleWriter(ConsoleWriter const&);
		void operator=(ConsoleWriter const&);
};

