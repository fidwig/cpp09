#include "BitcoinExchange.hpp"

std::map<std::string, float> BitcoinExchange::_btc_prices;

int BitcoinExchange::load_and_parse_csv(std::string filename)
{
	std::ifstream csv(filename.c_str());
	std::string line;
	
	if (!csv)
	return -1;
	csv.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (getline(csv, line))
	{
		std::string date;
		float btc_value;
		
		line[10] = ' ';
		// line.replace(line.begin(), line.end(), ',', ' ');
		// std::cerr << line << '\n';
		std::stringstream ss(line);
		ss >> date;
		ss >> btc_value;
		_btc_prices.insert(std::map<std::string, float>::value_type(date, btc_value));
	}

	// std::map<std::string, float>::iterator it;
	// for (it = _btc_prices.begin(); it != _btc_prices.end(); it++)
	// {
	// 	std::cout << it->first << " :: " << it ->second << std::endl;
	// }

	return 0;
}

float BitcoinExchange::get_price_at_date(std::string date)
{
	std::map<std::string, float>::iterator it = _btc_prices.lower_bound(date);
	if (it != _btc_prices.begin()) it--;
	return it->second;
}