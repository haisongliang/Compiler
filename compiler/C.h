#pragma once

#include <boost/spirit/include/qi.hpp>
#include <string>
#include <boost/fusion/include/adapt_struct.hpp>

template <typename Iterator>
struct Skipper :boost::spirit::qi::grammar<Iterator>
{
	boost::spirit::qi::rule<Iterator> start;
	
	Skipper() :Skipper::base_type(start)
	{
		using namespace boost::spirit::qi;
		start = space | "/*" >> *(char_ - "*/") >> "*/";
	}
};

struct C_Info
{
	std::string id;
};

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

	start = lexeme[(alpha | '_') >> *(alnum | '_')];
}

BOOST_FUSION_ADAPT_STRUCT(
	C_Info,
	(std::string, id)
)