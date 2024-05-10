#include "PmergeMe.hpp"
#include <climits>
#include <errno.h>
#include <sys/time.h>

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

void PmergeMe::add(std::deque<int> d)
{
    this->_d.operator=(d);
}

void PmergeMe::parse(const char*s)
{
    for(int i = 0; s[i]; i++)
    {
        if(!std::isdigit(s[i]))
            throw std::logic_error("Error");
    }
    char *ptr;
    long int i = strtol(s, &ptr, 10);
    if(errno == ERANGE || i < INT_MIN || i > INT_MAX)
        throw std::logic_error("Error");
}

template <typename T>
T merge(const T& left, const T& right)
{
    T result;
    typename T::const_iterator it = left.begin();
    typename T::const_iterator ite = right.begin();

    while(it != left.end() && ite != right.end())
    {
        if(*it < *ite)
        {
            result.push_back(*it);
            it++;
        }
        else
        {
            result.push_back(*ite);
            ite++;
        }
    }
    for(; it != left.end(); it++)
        result.push_back(*it);
    for(; ite != right.end(); ite++)
        result.push_back(*ite);
    return(result);
}

template <typename T>
T insertion_sort(T container)
{
    size_t i;
    size_t j;
    int key;
    for (i = 1; i < container.size() ; i++) {
        key = container[i];
        j = i;

        while (j > 0 && container[j - 1] > key) {
            container[j] = container[j - 1];
            j--;
        }
        container[j] = key;
    }
    return container;
}

template <typename T>
T merge_insert_sort(T container)
{
    if(container.size() <= 10)
        return(insertion_sort(container));
    
    typename T::iterator middle = container.begin() + (container.size() /2);

    T l(container.begin(), middle);
    T r(middle, container.end());
    
    l = merge_insert_sort(l);
    r = merge_insert_sort(r);
    return(merge(l, r));
}

double	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
        throw std::logic_error("gettimeofday() error");
	return ((double) (time.tv_sec * 1000000 + time.tv_usec));
}

template <typename T>
void print_container(T &container)
{
    typename T::iterator it = container.begin();
    for(; it != container.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void print_process(int size, std::string type ,double start, double end)
{
    std::cout << "Time to process a range of " << size << " elements with std::[" << type << "] :  " << end - start<< " us" << std::endl; 
}

void PmergeMe::sort()
{
    double curr_time = get_current_time();
    std::cout << "Before:   ";
    print_container<std::vector<int> >(this->_v);
    this->_v = merge_insert_sort<std::vector<int> >(this->_v);
    std::cout << "\n";
    std::cout << "After:   ";
    print_container<std::vector<int> >(this->_v);
    std::cout << "\n";
    print_process(this->_v.size(), "vector" ,curr_time, get_current_time());
    std::cout << "\n\n";
    curr_time = get_current_time();
    std::cout << "Before:   ";
    print_container<std::deque<int> >(this->_d);
    this->_d = merge_insert_sort<std::deque<int> >(this->_d);
    std::cout << "\n";
    std::cout << "After:   ";
    print_container<std::deque<int> >(this->_d);
    std::cout << "\n";
    print_process(this->_d.size(), "deque" , curr_time, get_current_time());
}

PmergeMe::~PmergeMe()
{
}

