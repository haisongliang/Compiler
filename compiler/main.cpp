#include <iostream>
#include <string>
#include "C.h"

int main(int argc, char** argv)
{
	std::wstring src = L"\t /*dfgsdf丹甫股份*/ \nsadf\n //dfgdsfgd";

	while (getline(std::wcin, src))
	{
		auto it = src.begin();
		C_Info info;
		C_Grammar<std::wstring::const_iterator> c_grammar;
		Skipper <std::wstring::const_iterator > skipper;
		bool result = boost::spirit::qi::phrase_parse(it, src.end(), c_grammar, skipper, info);
		if (result && it == src.end())
		{
			std::wcout << L"parse success!" << std::endl;
			std::wcout << info.id << std::endl;		
		}
		else
		{
			std::wcout << L"parse error!" << std::endl;
		}
	}

	return 0;
}
