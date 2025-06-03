#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange()
{
	loadDatabase();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	_data = other._data;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_data = other._data;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDatabase()
{
	std::ifstream db("data.csv");
	if (!db.is_open())
	{
		std::cerr << "Error: could not open database." << std::endl;
		std::exit(1);
	}

	std::string line;
	std::getline(db, line); // skip header

	while (std::getline(db, line))
	{
		std::istringstream iss(line);
		std::string date, valueStr;
		if (!std::getline(iss, date, ',') || !std::getline(iss, valueStr))
			continue;
		double value = std::atof(valueStr.c_str());
		_data[date] = value;
	}
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (size_t i = 0; i < date.size(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (date[i] < '0' || date[i] > '9')
			return false;
	}
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;
	return true;
}

bool BitcoinExchange::isNumber(const std::string& str) const
{
	if (str.empty())
		return false;
	size_t i = 0;
	if (str[0] == '+' || str[0] == '-')
		i = 1;
	bool hasDigit = false;
	bool hasDot = false;
	for (; i < str.size(); ++i)
	{
		if (str[i] == '.')
		{
			if (hasDot)
				return false;
			hasDot = true;
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			hasDigit = true;
		}
		else
			return false;
	}
	return hasDigit;
}

double BitcoinExchange::getRate(const std::string& date) const
{
	std::map<std::string, double>::const_iterator it = _data.lower_bound(date);
	if (it != _data.end() && it->first == date)
		return it->second;
	if (it == _data.begin())
		return -1; // no earlier date
	--it;
	return it->second;
}

void BitcoinExchange::processFile(const std::string& filename) const
{
	std::ifstream infile(filename.c_str());
	if (!infile.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	bool firstLine = true;
	while (std::getline(infile, line))
	{
		if (firstLine)
		{
			firstLine = false;
			continue;
		}
		if (line.empty())
			continue;

		std::istringstream iss(line);
		std::string date, sep, valueStr;
		if (!(std::getline(iss, date, '|')))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (!(std::getline(iss, valueStr)))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		// trim spaces
		while (!date.empty() && date[date.size() - 1] == ' ')
			date.erase(date.size() - 1);
		while (!valueStr.empty() && valueStr[0] == ' ')
			valueStr.erase(0, 1);

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}
		if (!isNumber(valueStr))
		{
			std::cerr << "Error: bad input => " << valueStr << std::endl;
			continue;
		}
		double value = std::atof(valueStr.c_str());
		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		double rate = getRate(date);
		if (rate < 0)
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		double result = value * rate;
		std::cout << date << " => " << value << " = " << result << std::endl;
	}
}
