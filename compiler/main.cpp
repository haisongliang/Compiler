#include <iostream>
#include <string>
#include "C.h"

int main(int argc, char** argv)
{
	std::string src = "asdfg";
	auto it = src.begin();
	C_Info info;
	C_Grammar<std::string::const_iterator> c_grammar;
	Skipper <std::string::const_iterator > skipper;
	bool result = boost::spirit::qi::phrase_parse(it, src.end(), c_grammar, skipper, info);
	if (result && it == src.end())
	{
		std::cout << "parse success!" << std::endl;
		std::cout << info.id << std::endl;		
	}
	else
	{
		std::cout << "parse error!" << std::endl;
	}

	return 0;
}
