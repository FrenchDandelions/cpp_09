#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    this->_odd = -1;
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
    this->_v.operator=(copy._v);
    this->_d.operator=(copy._d);
    this->_odd = copy._odd;
}

PmergeMe& PmergeMe::operator=(const PmergeMe &copy)
{
    if(this != &copy)
    {
        this->_odd = copy._odd;
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

void getJacobsthal(std::vector<int> &v)
{
    static const int jacob[31] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765};
    for(int i = 0; i < 31; i++)
        v.push_back(jacob[i]);
    return;
}

void printPrompt(char *color, const std::string &str)
{
    std::cout << color << "---------------------------------------------------"<< std::endl;
	std::cout << str << std::endl;
	std::cout << "---------------------------------------------------" RESET << std::endl;
}

void print_deque(const std::deque<int> &v)
{
    size_t size = v.size();

    std::cout << LIGHTB;
    for(size_t i = 0; i < size; i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << RESET "    with std::[deque] ";
}

void print_vector(const std::vector<int> &v)
{
    size_t size = v.size();

    std::cout << PURP;

    for(size_t i = 0; i < size; i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << RESET "    with std::[vector] ";
}

void PmergeMe::sort()
{
    sort_vector();
    std::cout << RESET "\n\n";
    sort_deque();
    std::cout << RESET ;
}

PmergeMe::~PmergeMe()
{
}

