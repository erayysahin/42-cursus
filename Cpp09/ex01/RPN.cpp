#include "RPN.hpp"
#include <sstream>
#include <iostream>
#include <cstdlib>

RPN::RPN() {}
RPN::RPN(const RPN& other) { static_cast<void>(other); }
RPN& RPN::operator=(const RPN& other)
{
	static_cast<void>(other);
	return *this;
}
RPN::~RPN() {}

bool RPN::isOperator(const std::string& token) const
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

int RPN::applyOp(int a, int b, const std::string& op) const
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

int RPN::evaluate(const std::string& expr) const
{
	std::istringstream iss(expr);
	std::stack<int> st;
	std::string token;
	while (iss >> token)
	{
		if (isOperator(token))
		{
			if (st.size() < 2)
				throw std::runtime_error("Error");
			int b = st.top(); st.pop();
			int a = st.top(); st.pop();
			int res = applyOp(a, b, token);
			st.push(res);
		}
		else
		{
			if (token.size() != 1 || token[0] < '0' || token[0] > '9')
				throw std::runtime_error("Error");
			int value = std::atoi(token.c_str());
			st.push(value);
		}
	}
	if (st.size() != 1)
		throw std::runtime_error("Error");
	return st.top();
}
