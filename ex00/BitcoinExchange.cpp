#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>

BTCExchange::BTCExchange()
{
}

BTCExchange::BTCExchange(const std::string &input_file)
{
    this->_input_file = input_file;
    this->getData();
    this->getInput();
}

BTCExchange::BTCExchange(const BTCExchange &copy)
{
    this->_input_file = copy._input_file;
    this->_input.operator=(copy._input);
    this->_data.operator=(copy._data);
    this->getData();
    this->getInput();
}

BTCExchange& BTCExchange::operator=(const BTCExchange &copy)
{
    if(this != &copy)
    {
        this->_input_file = copy._input_file;
        this->_data.operator=(copy._data);
        this->_input.operator=(copy._input);
        this->getData();
        this->getInput();
    }
    return(*this);
}

void BTCExchange::getData(void)
{
    std::ifstream file;
    file.open("data.csv");
    int i = 0;
    if(file.is_open())
    {
        while(1)
        {
            std::string line;
            if(!getline(file, line))
                break;
            i++;
            if(i == 1)
                continue;
            std::size_t it = line.find(',');
            if(it == std::string::npos)
                throw std::logic_error("Parsing error in the data.csv file, how?");
            std::string date = line.substr(0, it);
            double key = std::atof(line.substr(it + 1, line.size()).c_str());
            this->_data.insert(std::pair <std::string, double>(date, key));
        }
    }
    else
        throw std::logic_error("Error, couldn't open data.csv file");
}

int check_number(std::string &line, size_t it)
{
    int count_neg = 0;
    if(line[it])
        it++;
    if(line[it])
        it++;
    if(it == line.size())
        return(0);
    for(; it < line.size(); it++)
    {
        if(line[it] == '-')
            count_neg++;
        if(count_neg > 1 || (!std::isdigit(line[it]) && line[it] != '.' && line[it] != '-'))
            return (0);
    }
    return (1);
}

int check_date(std::string &date)
{
    int calendar[13] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    std::string year = date.substr(0, 4);
    std::string month = date.substr(5, 2);
    std::string day = date.substr(8, 2);
    int yearint = std::atoi(year.c_str());
    int monthint = std::atoi(month.c_str());
    int dayint = std::atoi(day.c_str());
    if(yearint < 2009 || monthint > 12 || dayint > calendar[monthint - 1])
        return (1);
    return(0);
}

void BTCExchange::getInput(void)
{
    std::ifstream input;
    input.open(this->_input_file.c_str());
    int i = 0;
    if(input.is_open())
    {
        while(1)
        {
            std::string line;
            int count = 0;
            if(!getline(input, line))
                break;
            if(i++ == 0)
                continue;
            std::size_t it = line.find('|');
            if(it == std::string::npos)
            {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }
            for(std::string::iterator ite = line.begin(); ite != line.end(); ite++)
            {
                if(*ite == '|')
                    break;
                if(*ite == '-')
                    count++;
            }
            if(count != 2 || it != 11 || !check_number(line, it))
            {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }
            std::string date = line.substr(0, it - 1);
            if(check_date(date))
            {
                std::cerr << "Error: invalid date." << std::endl;
                continue;
            }
            double key = std::atof(line.substr(it + 2, line.size()).c_str());
            if(key < 0 || key > 1000)
            {
                key < 0 ? std::cerr << "Error: not a positive number." << std::endl : std::cerr << "Error: too large a number." << std::endl;
                continue;
            }
            std::map<std::string, double>::iterator ite = this->_data.upper_bound(date);
            if(ite != this->_data.begin())
                ite--;
            // std::cout << ite->first << std::endl;
            std::cout << date << " => " << key * ite->second << std::endl;
        }
    }
    else
        throw std::logic_error("Error, couldn't open input file");
}

BTCExchange::~BTCExchange()
{
}