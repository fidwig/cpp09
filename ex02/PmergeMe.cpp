#include "PmergeMe.hpp"

//jacobsthal sequence class for convenience
JacobSthal::JacobSthal(): _prev(0), _current(0) {};
JacobSthal::JacobSthal(int n) {
	if (n == 0) { _prev = 0; _current = 0; }
	else if (n == 1) { _prev = 0; _current = 1; }
	_prev = jacobsthal_at_step_n(n - 1);
	_current = jacobsthal_at_step_n(n);
}
JacobSthal::~JacobSthal()
{}
int JacobSthal::jacobsthal_at_step_n(int n) {
	if (n <= 0)
		return 0;
	else if (n == 1)
		return 1;
	return (jacobsthal_at_step_n(n - 2) * 2 + jacobsthal_at_step_n(n - 1));
}
// int const & JacobSthal::get_prev() {
// 	return _prev;
// }
// int const & JacobSthal::get_current() {
// 	return _current;
// }
int JacobSthal::get_diff() {
	return _current - _prev;
}
int const & JacobSthal::next() {
	int keep = _current;
	_current = _current + _prev * 2;
	_prev = keep;
	return _current;
}

// int PmergeMe::parse(int ac, char **av)
// {
// 	if (ac == 2)
// 	{
// 		std::string arg(av[1]);
// 		std::stringstream ss(arg);
// 		int number;
// 		while (ss >> number)	
// 			_values.push_back(number);
// 		return 0;
// 	} else {
// 		for (int i = 1; i < ac; i++)
// 		{
// 			std::string arg(av[i]);
// 			std::stringstream ss(arg);
// 			int number;
// 			ss >> number;
// 			_values.push_back(number);
// 			if (ss >> number)
// 				return -1;
// 		}
// 		return 0;
// 	}
// 	// for (int i = 1; i < ac; i++)
// 	// {
// 	// 	std::string arg(av[i]);
// 	// 	std::stringstream ss(arg);
// 	// 	int number;
// 	// 	while (ss >> number)
// 	// 		v.push_back(number);
// 	// }
// }
