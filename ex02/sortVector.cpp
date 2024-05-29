#include "PmergeMe.hpp"

vec PmergeMe::makePair(std::vector<int> v)
{
    vec ve;
    if(v.size() % 2 != 0)
    {
        this->_odd = v.back();
        v.pop_back();
    }
    std::vector<int>::iterator it = v.begin();
    for(; it != v.end(); it += 2)
    {
        if(*it < *(it + 1))
            std::iter_swap(it, it + 1);
        ve.push_back(std::make_pair(*it, *(it + 1)));
    }
    return (ve);
}

void recursive(vec &v)
{
    if(v.size() <= 1)
        return;
    vec::iterator middle = v.begin() + (v.size() / 2);
    vec left(v.begin(), middle);
    vec right(middle, v.end());
    recursive(left);
    recursive(right);
    vec::iterator it = left.begin();
    vec::iterator ite = right.begin();
    size_t i = 0;
    while(it != left.end() && ite != right.end())
    {
        if(it->first < ite->first)
        {
            v[i] = *it;
            it++;
        }
        else
        {
            v[i] = *ite;
            ite++;
        }
        i++;
    }
    while(it != left.end())
        v[i++] = *it++;
    while(ite != right.end())
        v[i++] = *ite++;
}

int binarySearch(const std::vector<int>& v, int value, const std::vector<int>& jacob)
{
    int n = v.size();
    int low = 0;
    int high = n - 1;
    int jacob_idx = jacob.size();
    int mid = 0;

    while(low <= high)
    {
        jacob_idx--;
        if(jacob_idx < 0)
            mid = low;
        else
            mid = low + jacob[jacob_idx];
        if (mid >= n)
            mid = n - 1;
        if (v[mid] == value)
            return (mid);
        else if(v[mid] < value)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return(low);
}

void PmergeMe::sort_vector()
{
    clock_t start;
    clock_t end;

    printPrompt((char*)PURP, "TEST VECTOR:");
    std::cout << "Before: ";
    print_vector(this->_v);

    start = clock();

    std::vector<int> jacob;
    getJacobsthal(jacob);

    vec v = makePair(this->_v);
    vec::iterator it = v.begin();

    recursive(v);

    this->_v.clear();

    if(v.size() < 1)
    {
        this->_v.push_back(this->_odd);
        end = clock() - start;
        std::cout << "After: ";
        print_vector(this->_v);
        std::cout << "  took " << std::fixed << std::setprecision(5) << (static_cast<double>(end) / static_cast<float>(CLOCKS_PER_SEC)) * 1000 << " ms" << std::endl;
        if(is_sorted<std::vector<int> >(this->_v) == true)
            std::cout << RESET GREEN "all good mate" RESET << std::endl;
        else
            std::cout << RESET PURP "oops" RESET << std::endl;
        return;
    }

    this->_v.push_back(v[0].second);
    for(it = v.begin(); it != v.end(); it++)
        this->_v.push_back(it->first);
    
    std::cout << "\n\n";

    for(it = v.begin(); it != v.end(); it++)
    {
        if(it == v.begin())
            continue;
        int pos = binarySearch(this->_v, it->second, jacob);
        this->_v.insert(this->_v.begin() + pos, it->second);
    }

    if(this->_odd != -1)
    {
        int pos = binarySearch(this->_v, this->_odd, jacob);
        this->_v.insert(this->_v.begin() + pos, this->_odd);
    }

    end = clock() - start;

    std::cout << "After: ";
    print_vector(this->_v);
    std::cout << "  took " << std::fixed << std::setprecision(5) << (static_cast<double>(end) / static_cast<float>(CLOCKS_PER_SEC)) * 1000 << " ms" << std::endl;

    if(is_sorted<std::vector<int> >(this->_v) == true)
        std::cout << RESET GREEN "all good mate" RESET << std::endl;
    else
        std::cout << RESET PURP "oops" RESET << std::endl;
}
