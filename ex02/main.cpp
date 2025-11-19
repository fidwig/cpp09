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

void print_vector(std::vector<int> v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << (i == v.size() - 1 ? "" : " ");
	}
	// std::cout << std::endl;
}

void append_int_vector_to_vector(std::vector<int> &dst, std::vector<int> src)
{
	for (size_t i = 0; i < src.size(); i++)
		dst.push_back(src[i]);
}

std::vector<int> combine_int_vectors(std::vector<int> a, std::vector<int> b)
{
	for (size_t i = 0; i < b.size(); i++)
		a.push_back(b[i]);
	return a;
}

void print_pairs(std::vector<std::vector<int> > pairs)
{
	std::vector<std::vector<int> >::iterator it;

	for (it = pairs.begin(); it != pairs.end(); it++)
	{
		std::cout << "[";
		print_vector(*it);
		std::cout << "]";
		if (it + 1 != pairs.end())
			std::cout << ", ";
	}
}

void divide_pairs(std::vector<std::vector<int> > &seq)
{
	size_t big = seq[0].size();
	
	std::vector<std::vector<int> >::iterator it;

	for (it = seq.begin(); it != seq.end(); it++)
	{
		size_t size = it->size();
		if (size == big) {
			std::vector<int> half1;
			std::vector<int> half2;
			for (size_t i = 0; i < size; i++)
			{
				if (i < size / 2)
					half1.push_back((*it)[i]);
				else
					half2.push_back((*it)[i]);
			}
			seq.erase(it);
			seq.insert(it, half2);
			seq.insert(it, half1);
		}
	}		
	print_pairs(seq); std::cout << std::endl;
}

std::vector<int> build_final_vector(std::vector<std::vector<int> > seq)
{
	std::vector<int> clean_seq;
	std::vector<std::vector<int> >::iterator it;
	for (it = seq.begin(); it != seq.end(); it++)
		clean_seq.push_back(it->front());
	return clean_seq;
}

size_t binary_search_insert_index(std::vector<std::vector<int> > seq, int n, size_t limit /*a corresponding to the b i am inserting, if none limit == seq.size() - 1 or -1 will think about*/)
{
//TODO: binary search see papers in my pocker
}

//TODO: NAME
std::vector<int> name_later(std::vector<std::vector<int> > seq)
{
	std::vector<std::vector<int> > main;
	std::vector<std::vector<int> > pend;
	std::vector<std::vector<int> >::iterator sit;
	std::vector<std::vector<int> >::iterator mit;
	std::vector<std::vector<int> >::iterator pit;
	size_t current_size;
	// static int rec_level;
	divide_pairs(seq);
	current_size = seq[0].size();
	// setting up main, pend and non participating (remaining in seq)
	sit = seq.begin();
	size_t i = 0;
	while (sit != seq.end() && sit->size() == current_size)
	{
		if (i <= 1) //b1 a1
			main.push_back(*sit);
		else {
			if (i % 2 == 0) //b
				pend.push_back(*sit);
			else //a
				main.push_back(*sit);
		}
		sit++;
		i++;
	}

	int n; //jacobstahl number
	//how would i know where a(n) is once i have inserted some its not like they were labeled??
	//TODO: need to think about this
	//TODO: 

	//binary insertion
	// mit = main.begin();
	// pit = pend.begin();

	//add remaining from seq at end of main
	if (main[0].size() > 1)
		return name_later(main);
	return build_final_vector(seq);
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return EXIT_FAILURE;
	std::vector<int> v;
	// PmergeMe p;
	if (parse(v, argc, argv) < 0)
		return EXIT_FAILURE;
	print_vector(v); std::cout << std::endl;
	// print_vector(p.get_values());

	std::vector<std::vector<int> > pairs(v.size());
	std::vector<std::vector<int> > newpairs;

	for (size_t i = 0; i < v.size(); i++)
		pairs[i].push_back(v[i]);
// pair
	bool  bigger_pairs_possible = true;
	std::vector<std::vector<int> >::iterator it;
	int pair_size = 1;
	print_pairs(pairs); std::cout << std::endl;
	std::vector<int> no_pair;
	while (bigger_pairs_possible && pairs.size() > 1)
	{
		for (it = pairs.begin(); it != pairs.end(); it += 2)
		{
			if (it->size() > (it + 1)->size() || it + 1 == pairs.end())
			{
				if (it == pairs.begin()) bigger_pairs_possible = false;
				std::cout << "end of possible pairs of size " << (pair_size *= 2) << ", bigger pairs possible? " << (bigger_pairs_possible ? "true" : "false") << std::endl;
				break ;
			}
			if (it->back() >= (it + 1)->back())
			{
				std::cout << "pair: ["; print_vector(*(it + 1)); std::cout << " "; print_vector(*it); std::cout << "]" << std::endl;
				newpairs.push_back(combine_int_vectors(*(it + 1), *it));
			} else {
				std::cout << "pair: ["; print_vector(*it); std::cout << " "; print_vector(*(it + 1)); std::cout << "]" << std::endl;
				newpairs.push_back(combine_int_vectors(*it, *(it + 1)));
			}
		}
		for ((void) it; it != pairs.end(); it++)
			newpairs.push_back(*it);
		pairs = newpairs;
		newpairs.clear();
		print_pairs(pairs); std::cout << std::endl;
	}

	//----

	return EXIT_SUCCESS;
}