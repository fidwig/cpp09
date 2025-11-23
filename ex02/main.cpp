#include "PmergeMe.hpp"

void print_vector(std::vector<int> v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << (i == v.size() - 1 ? "" : " ");
	}
	// std::cout << std::endl;
}

/*TODO
make it a template so it works with multiple containers
revise logic

 I GOT IT ALL WRONG
 NOT THAT OVERCOMPLICATED

make pairs (ONCE)
sort those pairs internally
extract list each winner as main
extract list of each loser as pend
sort main using regular comparison sort apparently (or by calling ford-johnson recursively, much better imo)
insert pend in main using the jacobsthal thing
DONE hopefully
and all that with templates so i can use it with multiple containers !
(i like what i did here tho so i will back it up)
*/


template <typename Container>
Container fordjohnson(Container c)
{
	//step 1 make sorted pairs (pairs are created sorted in their constructor)
	std::vector<Pair<int> > pairs;
	typename Container::iterator cit;
	// for (it = c.begin(); it != c.end(); it + 1 != c.end() ? it+=2 : it++)
	// {
	// 	pairs.push_back()
	// }
	for (cit = c.begin(); cit != c.end(); cit++)
	{
		if (cit + 1 != c.end()) {
			pairs.push_back(Pair(*cit, *cit + 1)) //pair
			cit++;
		} else
			pairs.push_back(Pair(*cit)); //single number
	}

	/*
	step 2 create main and pend lists containing:
	main: first small and all bigs
	pend: all remaining smalls
	*/
	Container main;
	Container pend;
	std::vector<std::Pair<int> >::iterator pit;
	for (pit = pairs.begin(); pit != pairs.end(); pit++)
	{
		// if (pit == pairs.begin())
		// 	main.push_back(pit->getSmall());
		// else
		// 	pend.push_back(pit->getSmall());
		(pit == pairs.begin() ? main : pend).push_back(pit->getSmall());
		if (pit->isPair())
			main.push_back(pit->getBig());
	}
	/*
	step 3: sort main (original ford-johnson calls for any comparison sort, in this case i will use ford-johnson recursively)
	need to figure out how to sort while keeping each small tied to its big
	*/

	/*
	step 4;
	jacobsthal merge insert thing
	fairly easy to do i think
	*/
	return c;
}

int main(int argc, char **argv) //TODO: USE AT LEAST TWO DIFFERENT CONTAINERS FFS
{
	if (argc < 2)
		return EXIT_FAILURE;
	std::vector<int> v;
	// PmergeMe p;
	if (parse(v, argc, argv) < 0)
		return EXIT_FAILURE;
	print_vector(v); std::cout << std::endl;
	// print_vector(p.get_values());

	fordjohnson(v);

	return EXIT_SUCCESS;
}