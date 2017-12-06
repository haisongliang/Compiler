#pragma once

#define BOOST_SPIRIT_UNICODE 
#include <boost/spirit/include/qi.hpp>
#include <string>
#include <boost/fusion/include/adapt_struct.hpp>


template <typename Iterator>
struct Skipper :boost::spirit::qi::grammar<Iterator>
{
	boost::spirit::qi::rule<Iterator> start;

	Skipper() :Skipper::base_type(start)
	{
		using namespace boost::spirit::unicode;
		start = space
			| L"/*" >> *(char_ - L"*/") >> L"*/"
			| L"//" >> *char_ >> (boost::spirit::eoi| boost::spirit::eol);
		//L"//" >> *(char_  - boost::spirit::eol ) >> boost::spirit::eol;;
	}
};

struct identifier
{
	std::wstring id;// not necessary now.
	//std::string id;
};

struct C_Info
{
	//int a;
	std::wstring id;

	//C_Info() {}
	//C_Info(std::string str) :id(str) {}
	//C_Info(const char str) { id = str; }
	//C_Info(const char* str) :id(str) {}
};

BOOST_FUSION_ADAPT_STRUCT(
	C_Info,
	//(int, a)
	(std::wstring, id)
)

//static inline std::ostream& operator<<(std::ostream& os, C_Info const& id) {
//	return os << id.id;
//}

template <typename Iterator>
struct C_Grammar :boost::spirit::qi::grammar<Iterator, C_Info(), Skipper<Iterator>>
{
	C_Grammar();

	boost::spirit::qi::rule<Iterator, C_Info(), Skipper<Iterator>> start;
};

template <typename Iterator>
C_Grammar<Iterator>::C_Grammar() :C_Grammar::base_type(start)
{
	using namespace boost::spirit::qi;

	start = eps >> raw[lexeme[(unicode::alpha | L'_') >> *(unicode::alnum | L'_')]];
}

