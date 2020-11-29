#pragma once
#include <unordered_map>
#include "JackToken.hpp"

using namespace std;

class JackTokenFactory
{
private:
	unordered_map<string, Keyword> _keyword_map;
	unordered_map<char, int> _symbols;
	static JackTokenFactory* _instance;

	JackTokenFactory()
	{
		_keyword_map["class"] = Keyword::Class;
		_keyword_map["constructor"] = Keyword::Constructor;
		_keyword_map["function"] = Keyword::Function;
		_keyword_map["method"] = Keyword::Method;
		_keyword_map["field"] = Keyword::Field;
		_keyword_map["static"] = Keyword::Static;
		_keyword_map["var"] = Keyword::Var;
		_keyword_map["int"] = Keyword::Int;
		_keyword_map["char"] = Keyword::Char;
		_keyword_map["boolean"] = Keyword::Boolean;
		_keyword_map["void"] = Keyword::Void;
		_keyword_map["true"] = Keyword::True;
		_keyword_map["false"] = Keyword::False;
		_keyword_map["null"] = Keyword::Null;
		_keyword_map["this"] = Keyword::This;
		_keyword_map["let"] = Keyword::Let;
		_keyword_map["do"] = Keyword::Do;
		_keyword_map["if"] = Keyword::If;
		_keyword_map["else"] = Keyword::Else;
		_keyword_map["while"] = Keyword::While;
		_keyword_map["return"] = Keyword::Return;

		_symbols['{'] = 1;
		_symbols['}'] = 1;
		_symbols['('] = 1;
		_symbols[')'] = 1;
		_symbols['['] = 1;
		_symbols[']'] = 1;
		_symbols['.'] = 1;
		_symbols[','] = 1;
		_symbols[';'] = 1;
		_symbols['+'] = 1;
		_symbols['-'] = 1;
		_symbols['*'] = 1;
		_symbols['/'] = 1;
		_symbols['&'] = 1;
		_symbols['|'] = 1;
		_symbols['<'] = 1;
		_symbols['>'] = 1;
		_symbols['='] = 1;
		_symbols['~'] = 1;
	}

public:

	static JackTokenFactory* getInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new JackTokenFactory{};
		}
		return _instance;
	}

	Keyword keywordFromString(string keyword)
	{
		return _keyword_map[keyword];
	}

	Symbol symbolFromChar(char symbol)
	{
		return (Symbol)symbol;
	}

	JackToken* tokenFromString(string text)
	{
		JackToken* token = new JackToken{};
		token->keyword = Keyword::Unknown;
		token->token = TokenType::Unknown;

		//PROJECT 10 TODO: Use IF statements and Table 10.5 Lexical Elements to figure out what kind of token 
		//the supplied text variable represents.  
		token->rawText = text;

		if (_keyword_map.find(text) != _keyword_map.end())
		{
			//this token is a keyword
			token->keyword = _keyword_map[text];
			token->token = TokenType::Keyword;
		}
		else if (_symbols.find(text[0]) != _symbols.end() && text.length() == 1)
		{
			//token is a symbol
			token->symbol = (Symbol)text[0];
			token->token = TokenType::Symbol;
		}
		else if (text[0] == '"')
		{
			//token is a string constant
			token->string_value = text.substr(1, text.size() - 2);
			token->token = TokenType::StringConstant;
		}
		else if (text[0] < '0' || text[0] > '9')
		{
			//token is an identifier
			token->identifier = text;
			token->token = TokenType::Identifier;
		}
		else
		{
			//integer constant
			token->int_value = stoi(text);
			token->token = TokenType::IntegerConstant;
		}

		return token;
	}
};

JackTokenFactory* JackTokenFactory::_instance = nullptr;