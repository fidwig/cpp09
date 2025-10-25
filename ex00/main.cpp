#include "BitcoinExchange.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
		return 1;
		// return error(BADFILE), 1;
	if (BitcoinExchange::load_and_parse_csv("data.csv") < 0)
		return std::cerr << "Error: could not open/parse database" << std::endl, 1;

	std::ifstream input(argv[1]);
	if (!input)
		return std::cerr << "Error: could not open file.\n", 1;
	std::string line;
	float held_btc;
	std::string date;
	// getline(input, line);
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (getline(input, line))
	{
		float held_worth;

		std::stringstream ss(line);
		ss >> date;
		ss.ignore(std::numeric_limits<std::streamsize>::max(), '|');
		ss >> held_btc;
		if (held_btc < 0)
		{
			std::cerr << "Error: not a positive number.\n";
			continue ;
		}
		if (held_btc > 2147483647.0) //TODO: float to int !!! not good
		{
			std::cerr << "Error: too large a number.\n";
			continue ;
		}
		held_worth = BitcoinExchange::get_price_at_date(date) * held_btc;
		//TODO: find price in between dates on db maybe
		std::cout << date << " => " << held_btc << " = " << held_worth << std::endl;
	}
}