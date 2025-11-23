#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <cstdlib>

template <typename Container = std::vector<int> >
class PmergeMe
{
private:
	Container _values;
public:
	int parse(int, char **);
	PmergeMe() {};
	PmergeMe(PmergeMe const &) {};
	~PmergeMe() {};
};

template <typename T>
class Pair {
private:
	T _big;
	T _small;
	bool _single;
public:
	Pair(T a): _single(true) /*single number, no pair*/ {
		_big = 0; _small = a;
	};
	Pair(T a, T b): _single(false) {
		if (a > b) {
			_big = a; _small = b;
		} else {
			_big = b; _small = a;
		}
	};
	bool hasPair() { return !single; };
	int getBig() { return _big; };
	int getSmall() { return _small; };
	~Pair() {};
};

#include "PmergeMe.hpp"

template<typename Container>
int parse(Container &c, int ac, char **av)
{
	if (ac == 2)
	{
		std::string arg(av[1]);
		std::stringstream ss(arg);
		int number;
		while (ss >> number)	
			c.push_back(number);
		return 0;
	} else {
		for (int i = 1; i < ac; i++)
		{
			std::string arg(av[i]);
			std::stringstream ss(arg);
			int number;
			ss >> number;
			c.push_back(number);
			if (ss >> number)
				return -1;
		}
		return 0;
	}
}

#endif