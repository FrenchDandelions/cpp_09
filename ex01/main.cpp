#include "RPN.hpp"

int main(int argc, char **argv)
{
    if(argc == 2)
    {
        try
        {
            RPN rpn;
            std::string str = argv[1];
            rpn.doRPN(str);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }        
    }
    else
    {
        std::cerr << "Error" << std::endl;
    }
    return (0);
}
