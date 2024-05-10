#include <iostream>
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    std::vector<int> v;
    std::deque<int> d;
    PmergeMe m;
    if(argc > 1)
    {
        try
        {
            for(int i = 1; argv[i]; i++)
            {
                m.parse(argv[i]);
                v.push_back(std::atoi(argv[i]));
                d.push_back(std::atoi(argv[i]));
            }
            m.add(v);
            m.add(d);
            m.sort();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return (1);
        }
    }
    else
    {
        std::cerr << "Error" << std::endl;
        return(1);
    }
    return (0);
}