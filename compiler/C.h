#pragma once

#define BOOST_SPIRIT_UNICODE 
#include <boost/spirit/include/qi.hpp>
#include <string>
#include <boost/fusion/include/adapt_struct.hpp>
#include "error_handler.hpp"
#include <list>

//�հ׷�(�ո�TAB�����е�), ע��
template <typename Iterator>
struct Skipper :boost::spirit::qi::grammar<Iterator>
{
	boost::spirit::qi::rule<Iterator> start;

	Skipper() :Skipper::base_type(start)
	{
		using namespace boost::spirit::unicode;
		start = space	//�հ�
			//����ע��
			| L"/*" >> *(char_ - L"*/") >> L"*/"
			//����ע��
			| L"//" >> *(char_ - (boost::spirit::eoi | boost::spirit::eol)) >> (boost::spirit::eoi | boost::spirit::eol);
	}
};

//��ʶ������
struct identifier_attr
{
	std::wstring id;
};

BOOST_FUSION_ADAPT_STRUCT(
	identifier_attr,
	(std::wstring, id)
)

//��ʶ��
template <typename Iterator>
struct identifier :boost::spirit::qi::grammar<Iterator, identifier_attr(), Skipper<Iterator>>
{
	boost::spirit::qi::rule<Iterator, identifier_attr(), Skipper<Iterator>> start;

	identifier() :identifier::base_type(start)
	{
		using namespace boost::spirit::qi;
		start = eps
			>> raw[lexeme[(unicode::alpha | L'_')
			>> *(unicode::alnum | L'_')]];
	}
};

struct C_Grammar_attr
{
	int i;
	identifier_attr id;
	//std::wstring id;
};

BOOST_FUSION_ADAPT_STRUCT(
	C_Grammar_attr,
	(int, i)
	(identifier_attr, id)
	//(std::wstring, id)
)

template <typename Iterator>
struct C_Grammar :boost::spirit::qi::grammar<Iterator, C_Grammar_attr(), Skipper<Iterator>>
{
	boost::spirit::qi::rule<Iterator, C_Grammar_attr(), Skipper<Iterator>> start;

	identifier<Iterator> id;

	C_Grammar(client::error_handler<Iterator>& handler) :C_Grammar::base_type(start)
	{
		using namespace boost::spirit::qi;

		start = int_ >> id;

		typedef boost::phoenix::function<client::error_handler<Iterator>> error_handler_function;
		on_error<fail>(start, error_handler_function(handler)
			((const char*)"Error! Expecting ", _4, _3));
	}
};



