#pragma once
class ConsoleReader
{
	public:
		static ConsoleReader &getInstance();
		string ReadLine();

	private:
		ConsoleReader();
		ConsoleReader(ConsoleReader const&);
		void operator=(ConsoleReader const&);
};

