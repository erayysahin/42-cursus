#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>

class RPN
{
public:
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	int evaluate(const std::string& expr) const;

private:
	bool isOperator(const std::string& token) const;
	int applyOp(int a, int b, const std::string& op) const;
};

#endif
