#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <ctime>

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(char **av, int ac);
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();

	void mergeInsertSortVector(int left, int right);
	void mergeInsertSortDeque(int left, int right);
	bool isPositiveInteger(const std::string &s);

	void printVec() const;
	const std::vector<int> &getVec() const;

	void printDeq() const;
	const std::deque<int> &getDeq() const;

private:
	std::vector<int> vec;
	std::deque<int> deq;

	static int Jacobsthal(int k);
	void sortVector();
	void sortDeque();
};

#endif