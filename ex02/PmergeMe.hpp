#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <cstdlib>

class PmergeMe
{
private:
	std::vector<int> _values;
	//std::deque dq;
public:
	int parse(int, char **);
	PmergeMe();
	PmergeMe(PmergeMe const &);
	~PmergeMe();
};

#endif