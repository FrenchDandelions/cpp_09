#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

# define RED "\033[1;31m"
# define RESET "\033[0m"
# define PURP "\033[1;95m"
# define PURP2 "\033[1;35m"
# define ORANGE "\033[1;91m"
# define LIGHTB "\033[1;36m"
# define BLUE "\033[1;94m"
# define GREEN "\033[1;92m"
# define YELLOW "\033[1;93m"

class PmergeMe
{
    private:
        std::vector<int> _v;
        std::deque<int> _d;

    public:
        PmergeMe();
        PmergeMe(const PmergeMe& copy);
        PmergeMe& operator= (const PmergeMe &copy);
        ~PmergeMe();
        void add(std::vector<int> v);
        void parse(const char* s);
        void sort();
};

#endif