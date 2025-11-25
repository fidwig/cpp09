#include "PmergeMe.hpp"
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

GROUPITERATORS !!!!
*/

// template <typename Container>
// typename Container::iterator binary_search_insert_iterator(Container & dest, typename Container::iterator it, typename Container::iterator upper_bound)
// {
// 	typename Container::iterator left = dest.begin();
// 	// typename Container::iterator right = dest.end();
// 	typename Container::iterator right = upper_bound;
// 	typename Container::iterator middle;

// 	while (left <= right)
// 	{
// 		middle = left + std::distance(left, right) / 2;
// 		if (*middle > *it) right = middle - 1;
// 		else left = middle + 1;
// 	}
// 	return left;
// }

template <typename Iterator>
Iterator binary_search_insert_iterator(Iterator begin, Iterator end, Iterator it)//, Iterator upper)
{
	Iterator left = begin;
	// typename Container::iterator right = dest.end();
	Iterator right = end;
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
				// iterator pos = binary_search_insert_iterator(main, pend.begin() + i, main.end() - 1);
				main.insert(pos, pend[i]);
				pend.erase(pend.begin() + i);
			}
			js.next();
		} else {
			for (iterator it = pend.begin(); it != pend.end(); it++)
			{
				iterator pos = binary_search_insert_iterator(main.begin(), main.end() - 1, it);
				// iterator pos = binary_search_insert_iterator(main, it, main.end() - 1);
				main.insert(pos, *it);
			}
			pend.clear();
		}
	}
}

/* would require chunk size overload too ffs
template <typename Container>
void jacobsthal_insert(Container & c, size_t group_size)
{
	JacobSthal js(3);


}
*/

/*
if the function takes group iterators as argument, it should work fine with the recursion == problem solved i think
*/
// template <template <class T, class Allocator = std::allocator<T> > class Container>
template <typename Container>
// Container fordjohnson_impl(GroupIterator begin, GroupIterator end)
// Container fordjohnson_impl(Container c) 
Container fordjohnson(Container c)
{
	typedef typename Container::iterator iterator;
	// if (std::distance(begin, end) <= 1) return ;
	// if (std::distance(begin, end) == 2) sort_2();
	if (c.size() <= 1) return c;
	else if (c.size() == 2) return sort_2(c);
/*
	step 1 make sorted pairs (pairs are created sorted in their constructor)
*/
	// std::vector<Pair<int> > pairs;
	iterator cit;
	// for (cit = c.begin(); cit != c.end(); cit++)
	// {
	// 	if (iter_next(cit) != c.end()) {
	// 		pairs.push_back(Pair(*cit, *iter_next(cit))) //pair
	// 		cit++;
	// 	} else
	// 		pairs.push_back(Pair(*cit)); //single number
	// }
/*
	step 2 create main and pend lists containing:
	main: first small and all bigs
	pend: all remaining smalls
	---doing step 1 and 2 at the same time actually and ditching pairs (they are only conceptual now)
	------might even ditch main and pend
	--------maybe not actually

	--change the whole thing again with those group_iterators lmao
	----will work v well tho
*/
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
	---- ^^^^^ with group iterators (no too complicated)
	-- will need to build main and pend afterwards tho
	sucks if i dont
*/
	main = fordjohnson(main);
	//rearange pend base on the new main order
/*
	step 4;
	jacobsthal merge insert thing
	fairly easy to do i think
	two options either i managed to sort the list of pairs right away in which case i will insert the smalls as described in the book tihng
	either i didnt in which case i will do as i originally planned and insert pend in main
*/
	jacobsthal_insert(main, pend);

	return main;
}

// template <typename Container>
// Container fordjohnson(Container c)
// {
// 	typename Container::iterator begin = c.begin();
// 	typename Container::iterator end = c.end();

	// GroupIterator gb(b, 1);
	// GroupIterator ge(e, 1);

	// fordjohnson_impl(GroupIterator(begin, 1), GroupIterator(end, 1));
// }


int main(int argc, char **argv) //TODO: USE AT LEAST TWO DIFFERENT CONTAINERS FFS
{
	if (argc < 2)
		return EXIT_FAILURE;
	std::vector<int> v;
	// PmergeMe p;
	if (parse(v, argc, argv) < 0)
		return EXIT_FAILURE;
	print_container(v); std::cout << std::endl;
	// print_vector(p.get_values());

	v = fordjohnson(v);

	print_container(v); std::cout << std::endl;

	return EXIT_SUCCESS;
}