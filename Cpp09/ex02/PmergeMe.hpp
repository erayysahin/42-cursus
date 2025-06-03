#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	static void sortVector(std::vector<int>& container);
	static void sortDeque(std::deque<int>& container);

private:
	template <typename Container>
	static void mergeInsertSort(Container& cont);

	PmergeMe(int dummy); // prevent instantiation
};

#endif
