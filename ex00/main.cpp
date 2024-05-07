#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    try
    {
        (void)argc;
        std::string str = argv[1];
        BTCExchange BTC(str);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return (0);
}
