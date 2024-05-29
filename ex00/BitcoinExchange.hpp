#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <algorithm>

class BTCExchange
{
    private:
        BTCExchange();
        std::string _input_file;
        std::map<std::string, double> _data;
        std::map<std::string, double> _input;
        void getData();
        void getInput();

    public:
        BTCExchange(const std::string &input_file);
        BTCExchange(const BTCExchange &copy);
        BTCExchange& operator=(const BTCExchange &copy);
        ~BTCExchange();
};

#endif
