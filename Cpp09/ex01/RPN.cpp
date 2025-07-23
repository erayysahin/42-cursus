#include "RPN.hpp"
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <stack>

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
			throw std::runtime_error("Division by zero error");
		return a / b;
	}
	throw std::runtime_error("Invalid operator error");
}

int RPN::evaluate(const std::string &expr) const
{
	std::istringstream str(expr);
	std::stack<int> stack;
	std::string token;

	while (str >> token)
	{
		if (isOperator(token))
		{
			if (stack.size() < 2)
				throw std::runtime_error("Invalid RPN expression: insufficient operands");
			int b = stack.top();
			stack.pop();
			int a = stack.top();
			stack.pop();
			stack.push(applyOp(a, b, token));
		}
		else
		{
			int value = std::atoi(token.c_str());
			if (value > 9 || value < 0)
				throw std::runtime_error("Invalid number in RPN expression");
			stack.push(value);
		}
	}

	if (stack.size() != 1)
		throw std::runtime_error("Invalid RPN expression: leftover elements in stack");

	return stack.top();
}