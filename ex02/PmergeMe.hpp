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
	if (v.end() > v.begin() + n)
		std::cout << "[...] ";
}

template <typename Iterator>
class GroupIterator {
public:
	typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
	typedef typename std::iterator_traits<Iterator>::value_type value_type;
	typedef typename std::iterator_traits<Iterator>::pointer pointer;
	typedef typename std::iterator_traits<Iterator>::reference reference;

	typedef Iterator iterator_type;
	typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;
	// typedef std::random_access_iterator_tag iterator_category;
	
	GroupIterator() {}
	// GroupIterator(Iterator it): _it(it), _size(1)
	// {};
	GroupIterator(Iterator it, difference_type size): _it(it)/*std::move(it) ?*/, _size(size)
	{}

	iterator_type base() const {
		return _it;
	}

	difference_type size() const {
		return _size();
	}

	GroupIterator& operator ++() {
		std::advance(_it, _size);
		return *this;
	}

	GroupIterator& operator ++(int) {
		GroupIterator keep = *this;
		std::advance(_it, _size);
		return keep;
	} //TODO not sure about this one

	// --it it--;

	GroupIterator& operator +=(int const & incr) {
		std::advance(_it, _size * incr);
		return *this;
	} //TODO still not sure

	// -=

	bool operator ==(GroupIterator const & other)
	{
		return  _it == other.base();
		// return  a.base() == b.base() && a.size() == b.size(); maybe not actually
	}
	
	bool operator !=(GroupIterator const & other)
	{
		return  _it != other.base();
	}

	bool operator >(GroupIterator const & other)
	{
		return  _it > other.base();
	}

	bool operator <(GroupIterator const & other)
	{
		return  _it < other.base();
	}

	bool operator >=(GroupIterator const & other)
	{
		return  _it >= other.base();
	}

	bool operator <=(GroupIterator const & other)
	{
		return  _it <= other.base();
	}

	GroupIterator operator +(int const & n)
	{
		GroupIterator it = *this;
		it += n;
		return it;
	}

	value_type operator *()
	{
		return *_it; //TODO or *iter_next(_it, size - 1)
	}

	value_type * operator ->()
	{
		return &*_it; //TODO or &*iter_next(_it, size - 1)
	}

	// insert ?

	// friend GroupIterator operator +(GroupIterator a, GroupIterator b)
	// {
	// 	
	// 	return it;
	// }

	//iterator + iterator ?
	//iterator - iterator ?

	// friend GroupIterator operator -(GroupIterator it, int const & n)
	// {
	// 	it -= n;
	// 	return it;
	// }



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
	insert(GroupIterator pos, T value)
------------------------
	iter_swap(GroupIterator lhs, GroupIterator rhs) //swaps whole groups (from _it to _it + _size-1)
------------------------
	*/
private:
	Iterator _it;
	difference_type _size;
};

template <typename Iterator>
Iterator iter_next(Iterator iterator, typename std::iterator_traits<Iterator>::difference_type distance = 1)
{
	// while (--increment > 0)
	// 	iterator++;
	std::advance(iterator, distance);
	return iterator;
}

template <typename Iterator>
void iter_swap(GroupIterator<Iterator> a, GroupIterator<Iterator> b)
{
	using std::swap;
	
	Iterator first_a = a.base();
	Iterator first_b = b.base();
	Iterator last_a = iter_next(first_a, a.size() - 1);
	while (first_a <= last_a)
	{
		swap(*first_a, *first_b);
		first_a++;
		first_b++;
	}
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