#include <iostream>
#include <string>
#include <deque>
#include <iomanip>
#include <vector>
#include <typeinfo>
#include <list>

#if LIB //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	#include <iterator>
	namespace ft = std;
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

	{
		outputTitle("Vector: Complex Structures");
		ft::vector<Cat> CatContainer(6);
		std::cout << "There are  " << CatContainer.size() << " Kittens in the Cat Container and you can put up to " << CatContainer.capacity() << ".\n";
		
		const Cat* cat = new Cat();
		CatContainer.push_back(*cat);
		CatContainer.insert(CatContainer.begin(), *cat);
		std::cout << "There are " << CatContainer.size() << " Kittens in the Cat Container and you can put up to " << CatContainer.capacity() << ".\n";
		CatContainer.insert(CatContainer.begin(), 3, *cat);
		std::cout << "There are " << CatContainer.size() << " Kittens in the Cat Container and you can put up to " << CatContainer.capacity() << ".\n";
		std::cout << "First Cat in Cat Container has following thoughts: \n\t" << CatContainer[0].getBrain()->getIdea(0) << "\n";
		CatContainer[0].getBrain()->setIdea(0, "I'd like to have my own Container. If I fits, I sits ^-^");
		ft::vector<Cat> catContainer2(5, *cat);
		std::cout << "There are " << catContainer2.size() << " Kittens in the Cat Container 2 and you can put up to " << catContainer2.capacity() << ".\n";
		catContainer2.insert(catContainer2.begin() + 2, CatContainer.begin(), CatContainer.end());
		std::cout << "There are " << catContainer2.size() << " Kittens in the Cat Container 2 and you can put up to " << catContainer2.capacity() << ".\n";
		std::cout << "First Cat in Cat Container 2 has following thoughts: \n\t" << catContainer2[2].getBrain()->getIdea(0) << ".\n";
		catContainer2[2].getBrain()->setIdea(0, "\n\n  ,-.       _,---._ __  / \\\n /  )    .-'       `./ /   \\\n(  (   ,'            `/    /|\n \\  `-\\              '\\   / |\n  `.              ,  \\ \\ /  |\n   /`*          ,'-`----Y   |\n  (            ;        |   '\n  |  ,-.    ,-'         |  /\n  |  | (   |       42   | /\n  )  |  \\  `.___________|/\n  `--'   `--' \n\n");
		std::cout << "First Cat in Cat Container has following thoughts: \n\t" << CatContainer[0].getBrain()->getIdea(0) << "\n";
		std::cout << "First Cat in Cat Container 2 has following thoughts: \n\t" << catContainer2[2].getBrain()->getIdea(0) << "\n";
		delete (cat);
	}

	return (0);
}

