#include "PmergeMe.hpp"
/*TODO
try to maintain link between pend and main idk how tho atp i am considering sending it without this part i dont think it will be a problem
*/

template <typename Iterator>
Iterator binary_search_insert_iterator(Iterator begin, Iterator last, Iterator it)
{
	Iterator left = begin;
	Iterator right = last;
	Iterator middle;

	while (left <= right)
	{
		middle = left + std::distance(left, right) / 2;
		if (*middle > *it) right = middle - 1;
		else left = middle + 1;
	}
	return left;
}

template <typename Container>
void jacobsthal_insert(Container & main, Container & pend)
{
	typedef typename Container::iterator iterator;
	JacobSthal js(3);
	
	while (!pend.empty())
	{
		if (pend.size() >= (size_t) js.get_diff())
		{
			for (int i = js.get_diff() - 1; i >= 0; i--)
			{
				iterator pos = binary_search_insert_iterator(main.begin(), main.end() - 1, pend.begin() + i);
				main.insert(pos, pend[i]);
				pend.erase(pend.begin() + i);
			}
			js.next();
		} else {
			for (iterator it = pend.begin(); it != pend.end(); it++)
			{
				iterator pos = binary_search_insert_iterator(main.begin(), main.end() - 1, it);
				main.insert(pos, *it);
			}
			pend.clear();
		}
	}
}

template <typename Container>
Container fordjohnson(Container c)
{
	typedef typename Container::iterator iterator;
	if (c.size() <= 1) return c;
	else if (c.size() == 2) return sort_2(c);
/*
	step 1 make sorted pairs (pairs are created sorted in their constructor)
	step 2 create main and pend lists containing:
	main: first small and all bigs
	pend: all remaining smalls
	doing step 1 and 2 at the same time for convenience
*/
	iterator cit;
	Container main;
	Container pend;
	for (cit = c.begin(); cit != c.end(); cit++)
	{
		if (iter_next(cit) != c.end()) {
			if (*cit > *iter_next(cit))
				std::swap(*cit, *iter_next(cit));
			main.push_back(*iter_next(cit));
		}
		if (cit == c.begin()) main.push_back(*cit);
		else pend.push_back(*cit);
		if (iter_next(cit) != c.end())
			cit++;
	}
/*
	step 3: sort main (using ford-johnson recursively)
	TODO need to figure out how to sort while keeping each small tied to its big
	-- chunk size overload maybe like keep the whole original list and move em by whole chunks and only evaluate the last int of each chunk
	---- ^^^^^ sounds like the most sensible idea but fuck
	-- will need to build main and pend afterwards tho

	OR rearange pend base on the new main order after the sort? sound tedious for not much
*/
	main = fordjohnson(main);
/*
	step 4
	jacobsthal merge insert thing
	insert each pend item in main following the jacobsthal sequence order
	which is: 3-2 5-4 11-10-9-8-7-6 etc
	until the pend is too small to keep up with the order
	and insert the remaining in the regular order
*/
	jacobsthal_insert(main, pend);
	return main;
}

#include <ctime>
int main(int argc, char **argv) //TODO: USE AT LEAST TWO DIFFERENT CONTAINERS FFS
{
	if (argc < 2)
		return EXIT_FAILURE;
	std::vector<int> v;
	std::deque<int> d;
	// PmergeMe p;
	if (parse(v, argc, argv) < 0)
		return EXIT_FAILURE;
	if (parse(d, argc, argv) < 0)
		return EXIT_FAILURE;
	
	
	std::clock_t start;
	std::clock_t end;
	std::cout << "unsorted vector: ";print_container(v, 5); std::cout << std::endl;
	start = std::clock();
	v = fordjohnson(v);
	end = std::clock();
	std::cout << "sorted vector:   ";print_container(v, 5); std::cout << std::endl;
	std::cout << "took " << (static_cast<double>(end-start)/CLOCKS_PER_SEC) * 1000.0 * 1000.0 << "µs" << std::endl;

	std::cout << "unsorted deque: ";print_container(d, 5); std::cout << std::endl;
	start = std::clock();
	d = fordjohnson(d);
	end = std::clock();
	std::cout << "sorted deque:   ";print_container(d, 5); std::cout << std::endl;
	std::cout << "took " << (static_cast<double>(end-start)/CLOCKS_PER_SEC) * 1000.0 * 1000.0 << "µs" << std::endl;
	/*µ*/
	return EXIT_SUCCESS;
}