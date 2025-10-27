#include "RPN.hpp"

static bool issign(int c)
{
	return (c == '+' || c == '-' || c == '/' || c == '*');
}

int main(int ac, char **av)
{
	if (ac != 2)
		return std::cerr << "Error: usage: ./RPN <reverse polish mathematical expression>\n", -1;
	std::string expr(av[1]);

	for (size_t i = 0; i < expr.size(); i++)
	{
		if (!isdigit(expr[i]) && !issign(expr[i]) && !isspace(expr[i]))
			return std::cerr << "Error: forbidden character (\'" << expr[i] << "\')\n", -1;
		if (i > 0 && ((isdigit(expr[i]) && issign(expr[i - 1])) || (issign(expr[i]) && !isspace(expr[i - 1]))))
			return std::cerr << "Error: erroneous format\n", -1;
	}
	std::stringstream ss_expr(expr);
	std::string symbol;
	int value;
	std::streampos pos = ss_expr.tellg();
	std::stack<int> stack;
	while (ss_expr >> symbol)
	{
		if (isdigit(symbol[0])) {
			ss_expr.seekg(pos);
			ss_expr >> value;
			stack.push(value);
		}
		else {
			if (stack.size() < 2)
				return std::cerr << "Error: sign too early\n", -1; //TODO
			if (symbol == "+") {
				value = stack.top(); stack.pop();
				value += stack.top(); stack.pop();
				stack.push(value);
			} else if (symbol == "-") {
				value = stack.top(); stack.pop();
				value = stack.top() - value; stack.pop();
				stack.push(value);
			}else if (symbol == "/") {
				value = stack.top(); stack.pop();
				value = stack.top() / value; stack.pop();
				stack.push(value);
			}else if (symbol == "*") {
				value = stack.top(); stack.pop();
				value = value * stack.top(); stack.pop();
				stack.push(value);
			}
			else
				return std::cerr << "Error: invalid symbol\n", -1;
		}
		pos = ss_expr.tellg();
	}
	if (stack.size() != 1)
		return std::cerr << "Error: invalid expression (could not fully resolve)", -1;
	std::cout << stack.top() << std::endl;
	return 0;
}