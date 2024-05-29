#include "PmergeMe.hpp"

deq PmergeMe::makePair(std::deque<int> d)
{
    deq de;
    if(d.size() % 2 != 0)
    {
        this->_odd = d.back();
        d.pop_back();
    }
    std::deque<int>::iterator it = d.begin();
    for(; it != d.end(); it += 2)
    {
        if(*it < *(it + 1))
            std::iter_swap(it, it + 1);
        de.push_back(std::make_pair(*it, *(it + 1)));
    }
    return(de);
}

void recursive(deq &v)
{
    if(v.size() <= 1)
        return;
    deq::iterator middle = v.begin() + (v.size() / 2);
    deq left(v.begin(), middle);
    deq right(middle, v.end());
    recursive(left);
    recursive(right);
    deq::iterator it = left.begin();
    deq::iterator ite = right.begin();
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

int binarySearch(const std::deque<int>& v, int value, const std::vector<int>& jacob)
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

void PmergeMe::sort_deque(void)
{
    clock_t start;
    clock_t end;

    printPrompt((char*)LIGHTB, "TEST DEQUE:");
    std::cout << "Before: ";
    print_deque(this->_d);

    start = clock();

    std::vector<int> jacob;
    getJacobsthal(jacob);

    deq v = makePair(this->_d);
    deq::iterator it = v.begin();

    recursive(v);

    this->_d.clear();

    if(v.size() < 1)
    {
        this->_d.push_back(this->_odd);
        end = clock() - start;
        std::cout << "After: ";
        print_deque(this->_d);
        std::cout << "  took " << std::fixed << std::setprecision(5) << (static_cast<double>(end) / static_cast<float>(CLOCKS_PER_SEC)) * 1000 << " ms" << std::endl;
        if(is_sorted<std::deque<int> >(this->_d) == true)
            std::cout << RESET GREEN "all good mate" RESET << std::endl;
        else
            std::cout << RESET PURP "oops" RESET << std::endl;
        return;
    }

    this->_d.push_back(v[0].second);
    for(it = v.begin(); it != v.end(); it++)
        this->_d.push_back(it->first);
    
    std::cout << "\n\n";

    for(it = v.begin(); it != v.end(); it++)
    {
        if(it == v.begin())
            continue;
        int pos = binarySearch(this->_d, it->second, jacob);
        this->_d.insert(this->_d.begin() + pos, it->second);
    }

    if(this->_odd != -1)
    {
        int pos = binarySearch(this->_d, this->_odd, jacob);
        this->_d.insert(this->_d.begin() + pos, this->_odd);
    }

    end = clock() - start;

    std::cout << "After: ";
    print_deque(this->_d);
    std::cout << "  took " << std::fixed << std::setprecision(5) << (static_cast<double>(end) / static_cast<float>(CLOCKS_PER_SEC)) * 1000 << " ms" << std::endl;

    if(is_sorted<std::deque<int> >(this->_d) == true)
        std::cout << RESET GREEN "all good mate" RESET << std::endl;
    else
        std::cout << RESET PURP "oops" RESET << std::endl;
}
