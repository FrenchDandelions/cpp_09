#include "RPN.hpp"
#include <limits.h>
#include <cmath>
#include <climits>
#include <limits>
#include <iomanip>

RPN::RPN()
{
}

RPN::RPN(const RPN &copy)
{
    this->_s.operator=(copy._s);
}

RPN &RPN::operator=(const RPN &copy)
{
    if (this != &copy)
    {
        this->_s.operator=(copy._s);
    }
    return (*this);
}

RPN::~RPN()
{
}

int isOP(char c)
{
    if (c == '+' || c == '-' || c == '/' || c == '*')
        return (1);
    return (0);
}

void RPN::do_op(char c)
{
    if (this->_s.size() < 2)
        throw std::logic_error("Error\nNot enough numbers to do operation");
    double first = this->_s.back();
    this->_s.pop_back();
    double second = this->_s.back();
    this->_s.pop_back();
    if (c == '+')
    {
        double check = second + first;
        if(std::isinf(check) || check == std::numeric_limits<double>::max() || check == (std::numeric_limits<double>::max() * -1) || check == std::numeric_limits<double>::min())
            throw std::overflow_error("Error\nDouble Overflow/Double Underflow"); 
        this->_s.push_back(second + first);
    }
    else if (c == '-')
    {
        double check = second - first;
        if(std::isinf(check) || check == std::numeric_limits<double>::max() || check == (std::numeric_limits<double>::max() * -1) || check == std::numeric_limits<double>::min())
            throw std::overflow_error("Error\nDouble Overflow/Double Underflow"); 
        this->_s.push_back(second - first);        
    }
    else if (c == '*')
    {
        double check = second * first;
        if(std::isinf(check) || check == std::numeric_limits<double>::max() || check == (std::numeric_limits<double>::max() * -1) || check == std::numeric_limits<double>::min())
            throw std::overflow_error("Error\nDouble Overflow/Double Underflow"); 
        this->_s.push_back(second * first);
    }
    else if (c == '/')
    {
        if (first == 0)
            throw std::logic_error("Error\nForbidden division by 0");
        double check = second / first;
        if(std::isinf(check) || check == std::numeric_limits<double>::max() || check == (std::numeric_limits<double>::max() * -1) || check == std::numeric_limits<double>::min())
            throw std::overflow_error("Error\nDouble Overflow/Double Underflow"); 
        this->_s.push_back(second / first);
    }
}

void RPN::doRPN(std::string &str)
{
    if (str.size() == 0)
        throw std::logic_error("Error\nEmpty statck");
    std::string::iterator it = str.begin();
    for (; it != str.end(); it++)
    {
        if (!isOP(*it) && *it != ' ' && !std::isdigit(*it))
            throw std::logic_error("Error\nInvalid input");
        if (std::isdigit(*it))
            this->_s.push_back((*it) - '0');
        if (isOP(*it))
            do_op(*it);
    }
    if (this->_s.size() != 1)
        throw std::logic_error("Error\nToo many numbers in stack");
    std::cout << this->_s.back() << std::endl;
}
