#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <iterator>

template <typename Container>
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

template <typename Iterator>
class GroupIterator {
public:
	typedef std::iterator_traits<Iterator>::difference_type difference_type;
	typedef std::iterator_traits<Iterator>::value_type value_type;
	typedef std::iterator_traits<Iterator>::pointer pointer;
	typedef std::iterator_traits<Iterator>::reference reference;

	typedef std::iterator_traits<Iterator>::iterator_category iterator_category;
	// typedef std::random_access_iterator_tag iterator_category;
	
	GroupIterator() {};
	GroupIterator(Iterator it, difference_type size): _it(it)/*std::move(it) ?*/, _size(size)
	{};

	pointer base() const {
		return _it;
	};

	difference_type size() const {
		return _size();
	};
	/*
	TODO
	operators:
	++it
	it++
	--it
	it--
	+=
	-=
	( - only if biderectional operator or random access)
	>
	<
	*it (dereference): return *(std::next(_it, _size - 1)) // dereferences last iterator (_it is first so _it +( _size - 1) is last)
	it-> : return &(operator*()) // adress of dereferenced
	== (compares base()s)
	!= (same ^^^^)
	> (same ^^^^)
	< (same ^^^^)
	>= (same ^^^^)
	<= (same ^^^^) ///// check friend keyword for some of those
	+
	-

------------------------
	iter_swap(GroupIterator lhs, GroupIterator rhs) //swaps whole groups (from _it to _it + _size-1)
------------------------
	*/
private:
	Iterator _it;
	difference_type _size;
};

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
	int const & get_diff();
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