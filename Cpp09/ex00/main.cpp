#include "BitcoinExchange.hpp"
#include <iostream>
#include <stdexcept>
int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
			throw std::runtime_error("Bad Argument.");
		BitcoinExchange btc;
		btc.processFile(argv[1]);
		return 0;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

}
