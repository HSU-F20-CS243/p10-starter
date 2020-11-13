#pragma once
#include "JackTokenizer.hpp" 
#include <string>
#include <sstream>
using namespace std;

class JackToken
{
public:
	TokenType token;
	Keyword keyword;
	string rawText;
	Symbol symbol;
	string identifier;
	int int_value;
	string string_value;

	string toString()
	{
		ostringstream result{};
		switch (token)
		{
		case TokenType::Identifier:
			result << "<identifier>" << identifier << "</identifier>";
			break;

		case TokenType::IntegerConstant:
			result << "<integerConstant>" << int_value << "</integerConstant>";
			break;

		case TokenType::Keyword:
			result << "<keyword>" << rawText << "</identifier>";
			break;

		case TokenType::StringConstant:
			result << "<stringConstant>" << string_value << "</stringConstant>";
			break;

		case TokenType::Symbol:
			result << "<symbol>" << (char)symbol << "</symbol>";
			break;

		default:
			throw "unknown token type";
			break;
		}
		return result.str();
	}
};