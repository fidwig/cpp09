#include "PmergeMe.hpp"

template<typename Container = std::vector<int>>
Container parse(Container &c, int ac, char **av)
{
	if (ac == 2)
	{
		std::string arg(av[1]);
		std::stringstream ss(arg);
		int number;
		while (ss >> number)	
			v.push_back(number);
		return 0;
	} else {
		for (int i = 1; i < ac; i++)
		{
			std::string arg(av[i]);
			std::stringstream ss(arg);
			int number;
			ss >> number;
			v.push_back(number);
			if (ss >> number)
				return -1;
		}
		return 0;
	}
}