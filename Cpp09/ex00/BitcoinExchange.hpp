#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void processFile(const std::string& filename) const;

private:
	std::map<std::string, double> _data;
	void loadDatabase();

	std::string isValidDate(const std::string& date) const;
	bool isNumber(const std::string& str) const;
	double getRate(const std::string& date) const;
};

#endif
