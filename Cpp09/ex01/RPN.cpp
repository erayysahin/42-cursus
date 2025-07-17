#include "RPN.hpp"
#include <sstream>
#include <iostream>
#include <cstdlib>

RPN::RPN() {}
RPN::RPN(const RPN &other) { static_cast<void>(other); }
RPN &RPN::operator=(const RPN &other)
{
	static_cast<void>(other);
	return *this;
}
RPN::~RPN() {}

bool RPN::isOperator(const std::string &token) const
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

int RPN::applyOp(int a, int b, const std::string &op) const
{
	if (op == "+")
		return a + b;
	if (op == "-")
		return a - b;
	if (op == "*")
		return a * b;
	if (op == "/")
	{
		if (b == 0)
			throw std::runtime_error("Error");
		return a / b;
	}
	throw std::runtime_error("Error");
}

int RPN::evaluate(const std::string &expr) const
{
	std::istringstream str(expr);
	std::stack<int> stack;
	std::string token;
	std::string arg;
	str >> arg;
	stack.push(atoi(arg.c_str()));
	if (stack.top() > 9)
		throw std::runtime_error("error");
	str >> arg;
	if (stack.size() != 1  || stack.top() > 9)
		throw std::runtime_error("error");
	stack.push(atoi(arg.c_str()));
	while (str >> token)
	{
		if (!isOperator(token))
			std::runtime_error()
	}
