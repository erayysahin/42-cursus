#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <deque>

static bool isPositiveInteger(const std::string& s)
{
	if (s.empty())
		return false;
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (s[i] < '0' || s[i] > '9')
			return false;
	}
	return true;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	std::vector<int> vec;
	std::deque<int> deq;
	for (int i = 1; i < argc; ++i)
	{
		std::string token = argv[i];
		if (!isPositiveInteger(token))
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}
		long value = std::atol(token.c_str());
		if (value <= 0)
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}
		vec.push_back(static_cast<int>(value));
		deq.push_back(static_cast<int>(value));
	}

	std::cout << "Before: ";
	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i];
		if (i + 1 < vec.size())
			std::cout << " ";
	}
	std::cout << std::endl;

	std::vector<int> vecCopy = vec;
	std::deque<int> deqCopy = deq;

	std::clock_t startVec = std::clock();
	PmergeMe::sortVector(vec);
	std::clock_t endVec = std::clock();
	double durationVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000.0;

	std::clock_t startDeq = std::clock();
	PmergeMe::sortDeque(deq);
	std::clock_t endDeq = std::clock();
	double durationDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000.0;

	std::cout << "After: ";
	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i];
		if (i + 1 < vec.size())
			std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << vecCopy.size() << " elements with std::vector : " << durationVec << " us" << std::endl;
	std::cout << "Time to process a range of " << deqCopy.size() << " elements with std::deque : " << durationDeq << " us" << std::endl;

	return 0;
}
