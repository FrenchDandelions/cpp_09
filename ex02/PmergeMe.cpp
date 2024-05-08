#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
    this->_v.operator=(copy._v);
    this->_d.operator=(copy._d);
}

PmergeMe& PmergeMe::operator=(const PmergeMe &copy)
{
    if(this != &copy)
    {
        this->_v.operator=(copy._v);
        this->_d.operator=(copy._d);
    }
    return(*this);
}

void PmergeMe::add(std::vector<int> v)
{
    this->_v.operator=(v);
}

void PmergeMe::parse(const char*s)
{
    for(int i = 0; s[i]; i++)
    {
        if(!std::isdigit(s[i]))
            throw std::logic_error("Error");
    }
}

template <typename T>
void merge_insert_sort(T &container)
{

}

template <typename T>
void print_container(T &container)
{
    
}

void PmergeMe::sort()
{
    merge_insert_sort(this->_v);
    print_container(this->_v);
    merge_insert_sort(this->_d);
    print_container(this->_d);
}

PmergeMe::~PmergeMe()
{
}

