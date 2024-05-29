#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <utility>
#include <climits>
#include <errno.h>
#include <ctime>
#include <iomanip>

# define RED "\033[1;31m"
# define RESET "\033[0m"
# define PURP "\033[1;95m"
# define PURP2 "\033[1;35m"
# define ORANGE "\033[1;91m"
# define LIGHTB "\033[1;36m"
# define BLUE "\033[1;94m"
# define GREEN "\033[1;92m"
# define YELLOW "\033[1;93m"

typedef std::pair<int, int> pairint;
typedef std::deque<pairint> deq;
typedef std::vector<pairint> vec;

class PmergeMe
{
    private:
        int _odd;
        std::vector<int> _v;
        std::deque<int> _d;
 
        vec makePair(std::vector<int> v);
        deq makePair(std::deque<int> d);
        void sort_vector();
        void sort_deque();

    public:
        PmergeMe();
        PmergeMe(const PmergeMe& copy);
        PmergeMe& operator= (const PmergeMe &copy);
        ~PmergeMe();
        void add(std::vector<int> v);
        void add(std::deque<int> d);
        void parse(const char* s);
        void sort();
};

template <typename T>
bool is_sorted(T &container)
{
    typename T::iterator it = container.begin();
    typename T::iterator me = it + 1;
    typename T::iterator end = container.end();
    while(me != end)
    {
        if(*it > *me)
        {
            std::cout << RED <<  *it << " " << *me << RESET<< std::endl;
            return(0);
        }
        me++;
        it++;
    }
    return(1);
}

void print_deque(const std::deque<int> &v);
void print_vector(const std::vector<int> &v);
void getJacobsthal(std::vector<int> &v);
void printPrompt(char *color, const std::string &str);

#endif
