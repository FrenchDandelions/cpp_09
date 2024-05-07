#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>

class BTCExchange
{
    private:
        BTCExchange();
        std::map<std::string, double> _data;
        std::map<std::string, double> _input;

    public:
        BTCExchange(const std::string &input_file);
        BTCExchange(const BTCExchange &copy);
        BTCExchange& operator=(const BTCExchange &copy);
        ~BTCExchange();
};

BTCExchange::BTCExchange(/* args */)
{
}

BTCExchange::~BTCExchange()
{
}


#endif