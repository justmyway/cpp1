#pragma once
class ConsoleReader
{
	public:
		static ConsoleReader &getInstance();

	private:
		ConsoleReader();
		ConsoleReader(ConsoleReader const&);
		void operator=(ConsoleReader const&);
};

