#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <iomanip>
#include <limits>
#include <iterator>
#include <stdint.h>

// enum e_errors {
	// BADFILE,
	// BADINPUT,
	// NOTPOS,
	// TOOLARGE
// };

class BitcoinExchange
{
private:
	static std::map<std::string, float> _btc_prices;
	BitcoinExchange();
	BitcoinExchange(BitcoinExchange const &);
public:
	virtual ~BitcoinExchange() = 0;

	static int		load_and_parse_csv(std::string);
	static float	get_price_at_date(std::string);
};

#endif