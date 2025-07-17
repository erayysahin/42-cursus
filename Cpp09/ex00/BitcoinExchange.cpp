#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>

BitcoinExchange::BitcoinExchange()
{
	loadDatabase();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	_data = other._data;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
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
		throw std::runtime_error("Error: could not open database.");
	}
	std::string line;
	std::getline(db, line);

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
bool isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
std::string BitcoinExchange::isValidDate(const std::string &date) const
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return "Error: bad input => ";
	for (size_t i = 0; i < date.size(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (date[i] < '0' || date[i] > '9')
			return "Error: bad input => ";
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	if (year < 2009)
		return "Database de 2009 dan once bitcoin verisi bulunmuyor => ";
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	if (month == 2)
	{
		if (day > (isLeapYear(year) ? 29 : 28))
			return "Error: Invalid day for February.";
	}
	if (month < 1 || month > 12)
		return "Error: bad input => ";
	if (day < 1 || day > 31)
		return "Error: bad input => ";
	return "";
}

bool BitcoinExchange::isNumber(const std::string &str) const
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

double BitcoinExchange::getRate(const std::string &date) const
{
	std::map<std::string, double>::const_iterator it = _data.lower_bound(date);

	if (it != _data.end() && it->first == date)
		return it->second;

	if (it == _data.begin())
		return -1;

	--it;
	return it->second;
}

void BitcoinExchange::processFile(const std::string &filename) const
{
	std::ifstream dbfile(filename.c_str());
	if (!dbfile.is_open())
	{
		throw std::runtime_error("dosya acilmadi.");
	}
	std::string line;
	while (std::getline(dbfile, line))
	{
		std::istringstream dpv(line);
		std::string date, value;
		if (!(dpv >> date >> value >> value))
		{
			std::cerr << "Error: bad input format." << std::endl;
			continue;
		}
		std::string err = isValidDate(date);
		if (!err.empty())
			std::cerr << err << date << std::endl;

		else if (!isNumber(value))
			std::cerr << "Error: bad input => " << value << std::endl;
		else
		{

			double rate = getRate(date);
			double amount = std::atof(value.c_str());
			if (amount < 0)
				std::cerr << "Error: not a positive number." << std::endl;
			else if (amount > 1000)
				std::cerr << "Error: too large a number." << std::endl;
			else if (rate == -1)
				std::cerr << "Error: no data for this date." << std::endl;
			else
				std::cout << date << " => " << amount << " = " << amount * rate << std::endl;
		}
	}
}
