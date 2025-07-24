#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <deque>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	PmergeMe fj(argv, argc);

	std::cout << "Before: ";
	fj.printVec();
	std::cout << std::endl;

	std::clock_t startVec = std::clock();
	fj.fordJohnsonSortVector();
	std::clock_t endVec = std::clock();
	double durationVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000.0;

	std::clock_t startDeq = std::clock();
	fj.fordJohnsonSortDeque();
	std::clock_t endDeq = std::clock();
	double durationDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000.0;

	std::cout << "After: ";
	fj.printVec();
	std::cout << std::endl;

	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << fj.getVec().size() << " elements with std::vector : " << durationVec << " us" << std::endl;
	std::cout << "Time to process a range of " << fj.getDeq().size() << " elements with std::deque : " << durationDeq << " us" << std::endl;

	return 0;
}
