#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cstdlib>

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other) { static_cast<void>(other); }
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	static_cast<void>(other);
	return *this;
}
PmergeMe::~PmergeMe() {}

template <typename Container>
void PmergeMe::mergeInsertSort(Container& cont)
{
	typedef typename Container::value_type T;
	size_t n = cont.size();
	if (n <= 1)
		return;

	std::vector<std::pair<T, T> > pairs;
	std::vector<T> leftovers;

	for (size_t i = 0; i + 1 < n; i += 2)
	{
		T a = cont[i];
		T b = cont[i + 1];
		if (a < b)
			pairs.push_back(std::make_pair(a, b));
		else
			pairs.push_back(std::make_pair(b, a));
	}
	if (n % 2 == 1)
		leftovers.push_back(cont[n - 1]);

	std::vector<T> winners;
	winners.reserve(pairs.size() + leftovers.size());
	for (typename std::vector<std::pair<T, T> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
		winners.push_back(it->second);
	if (!leftovers.empty())
		winners.push_back(leftovers[0]);

	mergeInsertSort(winners);

	Container sorted;
	sorted.assign(winners.begin(), winners.end());

	for (typename std::vector<std::pair<T, T> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		T loser = it->first;
		size_t left = 0;
		size_t right = sorted.size();
		while (left < right)
		{
			size_t mid = (left + right) / 2;
			if (sorted[mid] < loser)
				left = mid + 1;
			else
				right = mid;
		}
		typename Container::iterator pos = sorted.begin();
		std::advance(pos, left);
		sorted.insert(pos, loser);
	}

	cont.assign(sorted.begin(), sorted.end());
}

void PmergeMe::sortVector(std::vector<int>& container)
{
	mergeInsertSort(container);
}

void PmergeMe::sortDeque(std::deque<int>& container)
{
	mergeInsertSort(container);
}

