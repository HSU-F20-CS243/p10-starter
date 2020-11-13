#pragma once
#include <unordered_map>
#include "JackToken.hpp"

using namespace std;

class JackTokenFactory
{
private:
	unordered_map<string, Keyword> _keyword_map;
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

		//PROJECT 10 TODO: Use IF statements and Table 10.5 Lexical Elements to figure out what kind of token 
		//the supplied text variable represents.  
		token->rawText = text;

		//replace the three lines below with real code
		token->keyword = Keyword::Unknown;
		token->token = TokenType::Unknown;
		token->symbol = Symbol::Unknown;

		return token;
	}
};

JackTokenFactory* JackTokenFactory::_instance = nullptr;