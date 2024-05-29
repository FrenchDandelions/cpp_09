#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <algorithm>
# include <list>

# define RED "\033[1;31m"
# define RESET "\033[0m"
# define PURP "\033[1;95m"
# define PURP2 "\033[1;35m"
# define ORANGE "\033[1;91m"
# define LIGHTB "\033[1;36m"
# define BLUE "\033[1;94m"
# define GREEN "\033[1;92m"
# define YELLOW "\033[1;93m"

class RPN
{
    private:
        std::list<double> _s;
        RPN(const RPN &copy);
        RPN& operator=(const RPN &copy);
        void do_op(char c);

    public:
        RPN();
        ~RPN();
        void doRPN(std::string &str);
};

#endif
