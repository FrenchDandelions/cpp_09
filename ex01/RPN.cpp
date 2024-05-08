#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN& copy)
{
    this->_s.operator=(copy._s);
}

RPN& RPN::operator=(const RPN &copy)
{
    if(this != &copy)
    {
        this->_s.operator=(copy._s);
    }
    return(*this);
}

RPN::~RPN()
{
}

int isOP(char c)
{
    if(c == '+' || c == '-' || c == '/' || c == '*')
        return(1);
    return(0);
}

void RPN::do_op(char c)
{
    if(this->_s.size() < 2)
        throw std::logic_error("Error");
    int first = this->_s.top();
    this->_s.pop();
    int second = this->_s.top();
    this->_s.pop();
    if(c == '+')
        this->_s.push(second + first);
    else if(c == '-')
        this->_s.push(second - first);
    else if(c == '*')
        this->_s.push(second * first);
    else if(c == '/')
    {
        if(first == 0)
            throw std::logic_error("Error");
        this->_s.push(second / first);
    }
}

void RPN::doRPN(std::string &str)
{
    if(str.size() == 0)
        throw std::logic_error("Error");
    std::string::iterator it = str.begin();
    for(; it != str.end(); it++)
    {
        if(!isOP(*it) && *it != ' ' && !std::isdigit(*it))
            throw std::logic_error("Error");
        if(std::isdigit(*it))
            this->_s.push((*it) - '0');
        if(isOP(*it))
            do_op(*it);
    }
    if(this->_s.size() != 1)
        throw std::logic_error("Error");
    std::cout << this->_s.top() << std::endl;
}

