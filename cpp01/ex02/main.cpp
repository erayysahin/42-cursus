#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main()
{
	string String = "HI THIS IS BRAIN";
	string *stringPTR = &String;
	string &stringREF = String;

	cout << "Variable  : " << &String << endl;
	cout << "stringPTR : " << stringPTR << endl;
	cout << "stringREF : " << &stringREF  << endl << endl;

	cout << "Variable  : " << String << endl;
	cout << "stringPTR : " << *stringPTR << endl;
	cout << "stringREF : " << stringREF  << endl;
}