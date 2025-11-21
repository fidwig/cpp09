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
	size_t size;
	std::vector<std::vector<int> >::iterator it;

	if (big == 1)
		return ;
	for (it = seq.begin(); it != seq.end(); it++)
	{
		size = it->size();
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
			it = seq.erase(it);
			it = seq.insert(it, half2);
			it = seq.insert(it, half1);
		}
	}		
	print_pairs(seq); std::cout << " divided" << std::endl;
}

std::vector<int> build_final_vector(std::vector<std::vector<int> > seq)
{
	std::vector<int> clean_seq;
	std::vector<std::vector<int> >::iterator it;
	for (it = seq.begin(); it != seq.end(); it++)
		clean_seq.push_back(it->front());
	return clean_seq;
}

size_t binary_search_insert(std::vector<std::vector<int> > &seq, std::vector<int> item, size_t upper_bound /*a corresponding to the b i am inserting, if none upper_bound == seq.size() - 1 or -1 will think about*/)
{
//TODO: binary search see papers in my pocker
	int L = 0;
	int R = (upper_bound < seq.size() ? upper_bound : seq.size() - 1); // seq.size() - 1;
	size_t m;
	
	while (R >= L)
	{
		m = L + (R - L) / 2;
		if (seq[m].back() > item.back())
			R = m - 1;
		else
			L = m + 1;
	}
	seq.insert(seq.begin() + L, item);
	print_pairs(seq);
	std::cout << " --> inserted at " << L << std::endl;
	return L; //returns index of insertion (useless atp)
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
	int i = 0;
	// while (!seq.empty() && seq.front().size() == current_size)
	while (sit != seq.end() && sit->size() == current_size)
	{
		if (i <= 1) //b1 a1
			main.push_back(*sit);
		else if (i % 2 == 0) //b
			pend.push_back(*sit);
		else //a
			main.push_back(*sit);
		sit++;
		i++;
	}

	print_pairs(main); std::cout << " <-- main" << std::endl;
	print_pairs(pend); std::cout << " <-- pend" << std::endl;

	int js = 3; //jacobstahl number
	int pjs = 1;
	i = js - pjs - 1;
	//how would i know where a(n) is once i have inserted some its not like they were labeled??
	//TODO: need to think about this
	//TODO: 
	while (!pend.empty())
	{
		if ((int) pend.size() - 1 >= i)
		{
			for (size_t k = i + 1; k-- > 0;)
			{
				/*
				// inserting item <Bn> with n = pjs + i + 1
				// main[pjs + i + 1] -> <An> in starting main
				// maybe lookup table
				i need to figure out how to keep track of where each <A>
				is in the main when i insert so i can do the binary search accordingly
				*/
				binary_search_insert(main, pend[k], main.size());//pjs + k + 1);
				pend.erase(pend.begin() + k);
			}
			int keep = js; js = js + 2 * pjs; pjs = keep;
			i = js - pjs - 1; //index in pend from jacobsthal number
		} else {
			//inserting item <Bn> with n = pjs + [inserted count]

			binary_search_insert(main, pend.front(), main.size() - 1);
			pend.erase(pend.begin());
		}
	}
	//add remaining from seq at end of main
	while (sit != seq.end())
	{
		main.push_back(*sit);
		sit++;
	}
	if (main[0].size() > 1)
		return name_later(main);
	return build_final_vector(main);
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

	v = name_later(pairs);
	print_vector(v); std::cout << " <-- resulting vector";
	//----

	return EXIT_SUCCESS;
}