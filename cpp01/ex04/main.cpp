#include <iostream>
#include <fstream>


void replaceInFile(std::string filename, std::string s1, std::string s2)
{
	std::ifstream infile(filename.c_str());

	if (!infile.is_open())
	{
		std::cerr << "Error opening files!" << std::endl;
		return;
	}
	std::ofstream outfile((filename + ".replace").c_str());
	if (!outfile.is_open())
	{
		std::cerr << "Error opening files!" << std::endl;
		infile.close();
		return;
	}
	std::string line;
	while (std::getline(infile, line))
	{
		size_t pos  = line.find(s1);
		while (pos != std::string::npos)
		{
			line = line.substr(0, pos) + s2 + line.substr(pos + s1.length());
			pos = line.find(s1, pos + s2.length());
		}
		outfile << line << std::endl;
	}
	infile.close();
	outfile.close();
}

int main(int ac, char **av)
{
	if (ac < 4)
	{
		std::cout << "Usage: ./replace <filename> s1 s2" << std::endl;
		return 1;
	}
	std::string filename = av[1];
	std::string s1 = av[2];
	std::string s2 = av[3];
	if (s1.empty() || s2.empty())
	{
		std::cerr << "Error: s1 and s2 must not be empty!" << std::endl;
		return 1;
	}
	replaceInFile(filename, s1, s2);
	return 0;
}