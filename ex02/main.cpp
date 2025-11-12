#include "PmergeMe.hpp"

int parse(std::vector<int> &v, int ac, char **av)
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
	// for (int i = 1; i < ac; i++)
	// {
	// 	std::string arg(av[i]);
	// 	std::stringstream ss(arg);
	// 	int number;
	// 	while (ss >> number)
	// 		v.push_back(number);
	// }
}

void printvector(std::vector<int> v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << (i == v.size() - 1 ? "" : " ");
	}
	std::cout << std::endl;
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return -1;
	std::vector<int> v;
	if (parse(v, argc, argv) < 0)
		return -1;
	printvector(v);
}