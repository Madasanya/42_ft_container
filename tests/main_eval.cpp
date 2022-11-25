#include <iostream>
#include <string>
#include <deque>
#include <iomanip>
#include <vector>
#include <typeinfo>
#include <list>

#define NODES 500000

#if LIB //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	#include <iterator>
	namespace ft = std;
	#define TESTCASE 1
#else
	#include "../map.hpp"
	#include "../stack.hpp"
	#include "../vector.hpp"
	#include "../utils.hpp"
	#include <iostream>
	#include <sstream>
	#define TESTCASE 0
#endif

#include <stdlib.h>
#include "AAnimal.hpp"
#include "Cat.hpp"

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096

#include <sys/time.h>
typedef struct timeval	t_timeval;

int	gettime(t_timeval start)
{
	t_timeval	tv;
	int			tdiff;

	gettimeofday(&tv, NULL);
	tdiff = (tv.tv_sec - start.tv_sec) * 1000;
	tdiff += (tv.tv_usec - start.tv_usec) / 1000;
	return (tdiff);
}

void	outputTitle(std::string title)
{
	std::string	toPrint;
	int	size = 60;
	int	n;

	toPrint = " " + title + " ";
	n = toPrint.size();
	if (n > size)
	{
		toPrint = toPrint.substr(0, size - 2);
		toPrint[size - 4] = '.';
		toPrint[size - 3] = ' ';
		n = toPrint.size();
	}
	std::cout << std::endl << std::setfill('=') << std::setw(size) << "" << std::endl;
	std::cout << std::setw(size / 2) << toPrint.substr(0, n / 2);
	std::cout << toPrint.substr(n / 2, n);
	std::cout << std::setfill('=') << std::setw(size - size / 2 - n + n / 2) << "" << std::endl;
	std::cout << std::setfill('=') << std::setw(size) << "" << std::endl;
	std::cout << std::endl;
}

void print(int id, const ft::vector<int>& container)
{
	std::cout << id << ". ";	
	for (unsigned i=0; i<container.size(); ++i)
		std::cout << ' ' << container[i];
	std::cout << '\n';
}

void map_insert_test(ft::map<int, int> *mp, int min, int max)
{
	int n = min+(max-min)/2;
	mp->insert(ft::make_pair(n, n));
	if (max - min > 1)
	{
		map_insert_test(mp, min, n);
		map_insert_test(mp, n, max);
	}
}

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	// **************************************************

	outputTitle("Vector: Swap");

	{
		ft::vector<int> vec1, vec2;
		for(int i=0; i < 20; i++)
			vec1.push_back(i);
		vec2.push_back(100);
		ft::vector<int>::iterator itb, itm;
		itb = vec1.begin();
		itm = vec1.begin() + 2;
		std::cout << vec1.size() << " | " << vec2.size() << std::endl;
		std::cout << *itb << " | " << *itm << std::endl;
		vec1.swap(vec2);
		std::cout << *itb << " | " << *itm << std::endl;
		std::cout << vec1.size() << " | " << vec2.size() << std::endl;
	}

	// **************************************************
	{
		outputTitle("Map: Balanced Input");
		ft::map<int, int> map;

		t_timeval start;
		int elapsedTime;

		
		map_insert_test(&map, 0, NODES);
		gettimeofday(&start, NULL);
		for(int i = 0; i < NODES; i++)
			std::cout << map.find(i)->second << std::endl;
		elapsedTime = gettime(start);
		if (TESTCASE)
			std::cerr << "STD (unbalanced tree) elapsed time: " << elapsedTime << "ms\n";
		else
			std::cerr << "FT (unbalanced tree) elapsed time: " << elapsedTime << "ms\n";
	}
	// **************************************************
	{
		outputTitle("Map: Random Input");
		ft::map<int, int> map_rand;

		t_timeval start;
		int elapsedTime;

		for(int i = 0; i < NODES; i++)
			map_rand.insert(ft::make_pair(rand(), rand()));
		ft::map<int, int>::iterator it, ite;
		it = map_rand.begin();
		ite = --map_rand.end();
		gettimeofday(&start, NULL);
		for(; it->first < ite->first; it++)
			std::cout << map_rand.find(it->first)->second << std::endl;
		elapsedTime = gettime(start);
		if (TESTCASE)
			std::cerr << "STD (random tree) elapsed time: " << elapsedTime << "ms\n";
		else
			std::cerr << "FT (random tree) elapsed time: " << elapsedTime << "ms\n";
	}
	// **************************************************
	{
		outputTitle("Stack: Different Base Container");
		ft::stack<int, ft::vector<int> > stack_ft_vec;
		ft::stack<int,std::vector<int> > stack_std_vec;
		ft::stack<int, std::deque<int> > stack_std_deq;
		ft::stack<int, std::list<int> > stack_std_lst;

		stack_ft_vec.push(1);
		stack_std_vec.push(2);
		stack_std_deq.push(3);
		stack_std_lst.push(4);

		std::cout << stack_ft_vec.empty() << std::endl;
		std::cout << stack_std_vec.empty() << std::endl;
		std::cout << stack_std_deq.empty() << std::endl;
		std::cout << stack_std_lst.empty() << std::endl;
	}
	return (0);
}

