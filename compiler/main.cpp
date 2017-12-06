#include <iostream>
#include <string>
#include "C.h"
#include <fstream>
#include <codecvt>
#include <sstream>
#include "error_handler.hpp"

int main(int argc, char** argv)
{
	//读取文件名
	char const* filename;
	if (argc > 1)
	{
		filename = argv[1];
	}
	else
	{
		std::cerr << "Error: No input file provided." << std::endl;
		return 1;
	}

	std::wifstream wif(filename, std::ios_base::in);
	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	if (!wif)
	{
		std::cerr << "Error: Could not open input file: "
			<< filename << std::endl;
		return 1;
	}

	std::wstringstream buffer;
	buffer << wif.rdbuf();
	std::wstring source_code = buffer.str();

	typedef std::wstring::const_iterator iterator_type;
	iterator_type iter = source_code.begin();
	iterator_type end = source_code.end();
	client::error_handler<iterator_type> handler(iter, end);

	C_Grammar_attr info;
	C_Grammar<iterator_type> c_grammar(handler);

	Skipper <iterator_type> skipper;
	bool result = boost::spirit::qi::phrase_parse(iter, end, c_grammar, skipper, info);
	if (result && iter == end)
	{
		std::wcout << L"parse success!" << std::endl;
		//std::wcout << info.id.id << std::endl;
	}
	else
	{
		std::wcout << L"parse error!" << std::endl;
	}

	return 0;
}
