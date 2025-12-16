#include "PmergeMe.hpp"
/*TODO
try to maintain link between B and A idk how tho atp i am considering sending it without this part i dont think it will be a problem
*/

template <typename Iterator>
Iterator binary_search_insert_iterator(Iterator begin, Iterator last, int value_to_insert, size_t size)
{
	Iterator left = begin;
	Iterator right = last;
	Iterator middle;
	
	while (left <= right)
	{
		// Corrected logic for middle calculation:
		typename Iterator::difference_type dist_groups = std::distance(left, right) / size;
		typename Iterator::difference_type groups_to_advance = dist_groups / 2;
		middle = left;
		std::advance(middle, groups_to_advance * size);
		// middle = left + ((std::distance(left, right) / size) * size) / 2;
		if (*iter_next(middle, size - 1) > value_to_insert) right = middle - size;
		else left = middle + size;
	}
	return left;
}

template <typename Container>
void group_insert(Container & c, typename Container::iterator pos, typename Container::iterator it, size_t size)
{
	typedef typename Container::iterator iterator;
	iterator cit;
	for (cit = iter_next(it, size - 1); cit >= it; cit--)
		pos = c.insert(pos, *cit);
}

template <typename Container>
void jacobsthal_insert(Container & A, Container & B, size_t size)
{
	typedef typename Container::iterator iterator;
	JacobSthal js(3);
	iterator pjsit = B.begin();
	iterator jsit = B.begin() + (js.get_diff() - 1) * size;
	size_t insert_count = 0;

	// std::cerr << "--------------------------------------" << std::endl;
	while (jsit < B.end())
	{
		// std::cerr << js.get_diff() << "\tA: "; print_container(A, size);
		// std::cerr << "\n\tB: "; print_container(B, size); std::cout << std::endl;
		for (iterator it = jsit; it >= pjsit; std::advance(it, -size))
		{
			size_t b_index = js.get_current() - 2; //current index in B
			// paired bigger was at index b_index+1 in A at the start
			// but now it is (furthest it can be) at b_index+1+insert_count
			size_t search_limit_offset = (b_index + 1 + insert_count) * size;
			if (search_limit_offset > A.size()) search_limit_offset = A.size();
			iterator pos = binary_search_insert_iterator(A.begin(), iter_next(A.begin(), search_limit_offset - size), *iter_next(it, size - 1), size);
			group_insert(A, pos, it, size);
			insert_count++;
		}
		js.next();
		pjsit = iter_next(jsit, size);
		jsit += js.get_diff() * size;
	}
	// std::cerr << js.get_diff() << "\tA: "; print_container(A, size);
	// std::cerr << "\n\tB: "; print_container(B, size); std::cout << std::endl;
	iterator it;
	for (it = pjsit; iter_next(it, size - 1) < B.end(); std::advance(it, size))
	{
		size_t b_index = std::distance(B.begin(), it) / size; //curretn index in B
		size_t search_limit_offset = (b_index + 1 + insert_count) * size;
		if (search_limit_offset > A.size()) search_limit_offset = A.size();
		iterator pos = binary_search_insert_iterator(A.begin(), iter_next(A.begin(), search_limit_offset - size), *iter_next(it, size - 1), size);
		group_insert(A, pos, it, size);
		insert_count++;
	}
	for (; it < B.end(); it++) // push leftovers (smaller pairs) to the end of A
		A.push_back(*it);
}
/*
void jacobsthal_insert(Container & A, Container & B, size_t size)
{
	typedef typename Container::iterator iterator;
	JacobSthal js(3);
	
	iterator pjsit = B.begin();
	iterator jsit = B.begin() + (js.get_diff() - 1) * size;
	std::cout << "--------------------------------------" << std::endl; //TODO
	while (jsit < B.end())
	{
		std::cout << js.get_diff() << "\tA: "; print_container(A, size); //TODO
		std::cout << "\n\tB: "; print_container(B, size); std::cout << std::endl; //TODO 
		for (iterator it = jsit; it >= pjsit; std::advance(it, -size))
		{
			iterator pos = binary_search_insert_iterator(A.begin(), iter_prev(A.end(), size), *iter_next(it, size - 1), size);
			// iterator pos = binary_search_insert_iterator(A.begin(), A.end() - 1, B.begin() + i);
			group_insert(A, pos, it, size);
			// A.insert(pos, *it);
			// B.erase(it);
			for (size_t i = 0; i < size; i++)
				*(it + i) = 0;
		}
		js.next();
		pjsit = iter_next(jsit, size);
		jsit += js.get_diff() * size;

	//TODO group iteration
	}
	std::cout << js.get_diff() << "\tA: "; print_container(A, size); //TODO
	std::cout << "\n\tB: "; print_container(B, size); std::cout << std::endl; //TODO 
	iterator it;
	for (it = pjsit; iter_next(it, size - 1) < B.end(); std::advance(it, size))
	{
		iterator pos = binary_search_insert_iterator(A.begin(), iter_prev(A.end(), size), *iter_next(it, size - 1), size);
		group_insert(A, pos, it, size);
		// A.insert(pos, *it);
	}
	for (; it < B.end(); it++) //push leftover (smaller pairs) to the end of A to be inserted in the previous recursiom
	{
		A.push_back(*it);
	}
}
*/

template <typename Iterator>
void group_swap(Iterator ait, Iterator bit, typename Iterator::difference_type size)
{
	typedef typename Iterator::difference_type diff_type;

	using std::swap;
	diff_type i;
	for (i = 0; i < size; i++)
	{
		swap(*ait, *bit);
		ait++; bit++;
	}
}

template <typename Container>
Container group_sort_2(Container c, size_t size)
{
	typedef typename Container::iterator iterator;
	iterator fit = c.begin();
	iterator sit = iter_next(fit, size);
	if (*iter_next(fit, size - 1) > *iter_next(sit, size - 1))
		group_swap(fit, sit, size);
	return c;
}

template <typename Container>
void group_push_back(Container &c, typename Container::iterator it, size_t size)
{
	typedef typename Container::iterator iterator;
	iterator geit = it + size;
	for (; it < geit; it++)
	{
		c.push_back(*it);
	}
}

template <typename Container>
Container fordjohnson_impl(Container c, size_t size)
{
	typedef typename Container::iterator iterator;
	// if (c.size() <= 1) return c;
	// else if (c.size() == 2) return sort_2(c);

	if (c.size() / size <= 1) return c;
	// else if (c.size() / size == 2) return group_sort_2(c, size);
/*
	step 1 make sorted pairs (pairs are created sorted in their constructor)
	step 2 create A and B lists containing:
	A: first small and all bigs
	B: all remaining smalls
	doing step 1 and 2 at the same time for convenience
*/
	// std::cerr << "size: " << size << '\n';
	// std::cerr << "before in pair swaps: "; print_container(c, size); std::cerr << '\n';

	iterator cit;
	for (cit = c.begin(); iter_next(cit, size - 1) < c.end(); std::advance(cit, size * 2))
	//TODO group iteration
	{
		if (iter_next(cit, 2 * size - 1) < c.end()) {
			if (*iter_next(cit, size - 1) > *iter_next(cit, 2 * size - 1))
				group_swap(cit, iter_next(cit, size), size);
		}
	}
	// std::cerr << "after in pair swaps: "; print_container(c, size); std::cerr << '\n';
	// std::cerr << "--------<>--------\n";

	/*
	step 3: sort A (using ford-johnson recursively)
	TODO need to figure out how to sort while keeping each small tied to its big
	-- group size parameter maybe like keep the whole original list and move em by whole chunks and only evaluate the last int of each chunk
	---- ^^^^^ sounds like the most sensible idea but fuck i dooont waaant toooo
	*/
	c = fordjohnson_impl(c, size * 2);
// create A and B
	Container A;
	Container B;

	int i = 0;
	for (cit = c.begin(); cit + (size - 1) < c.end(); std::advance(cit, size))
	{
		if (i == 0 || i % 2) group_push_back(A, cit, size);
		else group_push_back(B, cit, size);
		i++;
	}
	
	////add leftover at end of B
	for (; cit < c.end(); cit++)
	{
		B.push_back(*cit);
	}
	
	/*
	either use A B and a list for the indexes of each a to keep track
	^^^^ i chose this ! and its done ffs i dont want to hear anything about it ever again
	*/

	/*
	step 4
	jacobsthal merge insert thing
	insert each B item in A following the jacobsthal sequence order
	which is: 3-2 5-4 11-10-9-8-7-6 etc
	so diff : 1-0 1-0 6-5-4-3-2-1-0
	until the B is too small to keep up with the order
	and insert the reAing in the regular order
	*/ // done <3
	// std::cerr << "-----------------------------\n" << "Size: " << size << "\nSorting list: " ; print_container(c, size); std::cerr << std::endl; //TODO
	// std::cerr << "\nlist A: " ; print_container(A, size); std::cerr << std::endl; //TODO
	// std::cerr << "\nlist B: " ; print_container(B, size); std::cerr << std::endl; //TODO
	jacobsthal_insert(A, B, size);
	return A;
}

template <typename Container>
Container fordjohnson(Container c)
{
	return fordjohnson_impl(c, 1);
}

int main(int argc, char **argv)
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

	//TODO change output format
	std::clock_t start;
	std::clock_t end;
	std::cout << "unsorted vector: ";print_container(v, 21); std::cout << std::endl;
	start = std::clock();
	v = fordjohnson(v);
	end = std::clock();
	std::cout << "sorted vector:   ";print_container(v, 21); std::cout << std::endl;
	std::cout << "time to process a range of " << v.size() << " elements with std::vector : " << (static_cast<double>(end-start)/CLOCKS_PER_SEC) * 1000.0 * 1000.0 << "µs" << std::endl;

	std::cout << "unsorted deque: ";print_container(d, 21); std::cout << std::endl;
	start = std::clock();
	d = fordjohnson(d);
	end = std::clock();
	std::cout << "sorted deque:   ";print_container(d, 21); std::cout << std::endl;
	std::cout << "time to process a range of " << v.size() << " elements with std::deque : " << (static_cast<double>(end-start)/CLOCKS_PER_SEC) * 1000.0 * 1000.0 << "µs" << std::endl;
	/*µ*/
	return EXIT_SUCCESS;
}