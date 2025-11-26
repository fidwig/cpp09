#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <iterator>

template <typename Container>
class PmergeMe
{
private:
	Container _values;
public:
	int parse(int, char **);
	PmergeMe() {}
	PmergeMe(PmergeMe const &) {}
	~PmergeMe() {}
};

template <typename Container>
void print_container(Container v, int n = -1)
{
	typename Container::iterator it;
	for (it = v.begin(); n != 0 && it != v.end() && (n == -1 || it < v.begin() + n - 1); it++)
	{
		std::cout << *it << " ";
	}
	if (v.end() == v.begin() + n)
		std::cout << *it << " ";
	if (v.end() > v.begin() + n && n != -1)
		std::cout << "[...] ";
}

template <typename Iterator>
Iterator iter_next(Iterator iterator, typename std::iterator_traits<Iterator>::difference_type distance = 1)
{
	// while (--increment > 0)
	// 	iterator++;
	std::advance(iterator, distance);
	return iterator;
}

template <typename Container>
void iter_swap(typename Container::iterator a, typename Container::iterator b)
{
	using std::swap;
	swap(*a, *b);
}

template <typename Container>
Container sort_2(Container c)
{
	if (c.front() > c.back())
		iter_swap(c.begin(), c.begin() + 1);
	return c;
}

class JacobSthal {
private:
	int _prev;
	int _current;
	int jacobsthal_at_step_n(int);
public:
	JacobSthal();
	JacobSthal(int);
	~JacobSthal();
	
	// int const & get_prev();
	// int const & get_current();
	int get_diff();
	int const & next();
};

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