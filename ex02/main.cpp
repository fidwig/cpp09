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

template <typename Iterator>
Iterator binary_search_insert_iterator(Iterator begin, Iterator last, Iterator it)//, Iterator upper)
{
	Iterator left = begin;
	// typename Container::iterator right = dest.end();
	Iterator right = last;
	Iterator middle;

	while (left <= right)
	{
		// middle = left + (right - left) / 2;
		middle = left + GroupIterator<typename Iterator::iterator_type>::distance(left, right) / 2;
		if (*middle > *it) right = middle - 1;
		else left = middle + 1;
	}
	return left;
}

// template <typename Container>
// void jacobsthal_insert(Container & main, Container & pend)
// {
// 	typedef typename Container::iterator iter;
// 	JacobSthal js(3);
	
// 	while (!pend.empty())
// 	{
// 		if (pend.size() >= (size_t) js.get_diff())
// 		{
// 			for (int i = js.get_diff() - 1; i >= 0; i--)
// 			{
// 				iterator pos = binary_search_insert_iterator(main.begin(), main.end() - 1, pend.begin() + i);
// 				// iterator pos = binary_search_insert_iterator(main, pend.begin() + i, main.end() - 1);
// 				main.insert(pos, pend[i]);
// 				pend.erase(pend.begin() + i);
// 			}
// 			js.next();
// 		} else {
// 			for (iterator it = pend.begin(); it != pend.end(); it++)
// 			{
// 				iterator pos = binary_search_insert_iterator(main.begin(), main.end() - 1, it);
// 				// iterator pos = binary_search_insert_iterator(main, it, main.end() - 1);
// 				main.insert(pos, *it);
// 			}
// 			pend.clear();
// 		}
// 	}
// }

// template <typename Container, template <class Iterator = typename Container::iterator> class GroupIter>
// void group_iter_move(Container c, GroupIter<> pos, GroupIter<> src)

template <typename Container>
void group_iter_move(Container c, GroupIterator<typename Container::iterator> pos, GroupIterator<typename Container::iterator> src)
{
	typedef typename Container::iterator iter;

	iter it;
	//TODO iterator might be invalidated here
	//should probably do a copy of src's items, erase src and then insert each at pos
	for (it = src.base() + src.size() - 1; it >= src.base(); it--) {
		pos = c.insert(pos.base(), *it);
	}
	c.erase(src.base(), src.base() + src.size() - 1);
}

template <typename Container>
void jacobsthal_insert(Container c, size_t size)
{
	typedef typename Container::iterator iter;
	JacobSthal js(3);

	GroupIterator<iter> begin(c.begin(), size);
	GroupIterator<iter> end(c.end(), size);

	GroupIterator<iter> jsit = begin + (js.get_diff() - 1) * 2 + 1/* + 1 == small index*/;
	GroupIterator<iter> pjsit = begin;
	while (jsit < end)
	{
		for (GroupIterator<iter> it = jsit; it >= pjsit; it -= 2)
		{
			// different types here ffs
			GroupIterator<iter> pos = binary_search_insert_iterator(begin, end - 1, it);
			// iterator pos = binary_search_insert_iterator(main, pend.begin() + i, main.end() - 1);
			// also need to figure out how to not lose track of the values position after inserting yk
			// aslo should skip and end loop if the "pair" were on is bigger than whats left, it means its an odd count and we shouldnt touch it
			group_iter_move(c, pos, it); //TODO group_iterator insert/move, inserts copy of value(s) from it at pos and removes original!! takes whole iterator and not value;
			// end loop if it
		}
		js.next();
		pjsit = iter_next(jsit, 2);
		jsit += js.get_diff() * 2;
	}
	for (GroupIterator<iter> it = pjsit; it < end; it += 2)
	{
		GroupIterator<iter> pos = binary_search_insert_iterator(begin, end, it);
		// iterator pos = binary_search_insert_iterator(main, it, main.end() - 1);
		group_iter_move(c, pos, it);
	}
}

// template <typename Iterator>
// // // Container fordjohnson_impl(Container c) 
// // int fordjohnson_impl(Iterator begin, Iterator end)
// void fordjohnson_impl(Iterator begin, Iterator end)
// {
// 	if (std::distance(begin, end) <= 1) return c;
// 	else if (std::distance(begin, end) == 2) return sort_2(begin, end);
// 	Iterator cit;
// 	for (cit = begin; cit != end; cit++)
// 	{
// 		if (iter_next(cit) != end) {
// 			if (*cit < *iter_next(cit))
// 				iter_swap(cit, iter_next(cit));
// 		}
// 		if (iter_next(cit) != end)
// 			cit++;
// 	}
// 	fordjohnson_impl(Iterator(begin.base(), begin.size() * 2), Iterator(end.base(), end.size() * 2));
// 	jacobsthal_insert(begin, end);
// 	return main;
// }

template <typename Container>
// // Container fordjohnson_impl(Container c) 
// int fordjohnson_impl(Iterator begin, Iterator end)
Container fordjohnson_impl(Container c, size_t size)
{
	typedef typename Container::iterator iter;

	if (c.size() <= 1) return c;
	else if (c.size() == 2) return sort_2(c);
	// iterator cit;
	GroupIterator<iter> cit(c.begin(), size);
	GroupIterator<iter> begin(c.begin(), size);
	GroupIterator<iter> end(c.end(), size);
	for (; cit < end; cit++)
	{
		if (iter_next(cit) != end) {
			if (*cit < *iter_next(cit))
				iter_swap(cit, iter_next(cit));
		}
		if (iter_next(cit) != end)
			cit++;
	}
	c = fordjohnson_impl(c, size * 2);
	jacobsthal_insert(c, size);
	return c;
}

template <typename Container>
Container fordjohnson(Container c)
{
	// typedef typename Container::iterator iter;
	// iter begin = c.begin();
	// iter end = endc.end();
	// fordjohnson_impl(GroupIterator<iter>(begin), GroupIterator<iter>(end));

	return fordjohnson_impl(c, 1);
}


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