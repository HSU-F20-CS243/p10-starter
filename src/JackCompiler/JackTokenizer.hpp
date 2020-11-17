#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iostream>
using namespace std;

enum class TokenType { Unknown = -1, Keyword, Symbol, Identifier, IntegerConstant, StringConstant };
enum class Keyword { Unknown = -1, Class, Method, Function, Constructor, Int, Boolean, Char, Void, Var, Static, Field, Let, Do, If, Else, While, Return, True, False, Null, This };
enum class Symbol {
	Unknown = -1,
	LeftCurlyBrace = (int)'{',
	RightCurlyBrace = (int)'}',
	LeftParentheses = (int)'(',
	RightParentheses = (int)')',
	LeftHardBracket = (int)'[',
	RightHardBracket = (int)']',
	Period = (int)'.',
	Comma = (int)',',
	SemiColon = (int)';',
	Plus = (int)'+',
	Minus = (int)'-',
	Asterisk = (int)'*',
	ForwardSlash = (int)'/',
	Ampersand = (int)'&',
	Pipe = (int)'|',
	LessThan = (int)'<',
	GreaterThan = (int)'>',
	Equal = (int)'=',
	Tilde = (int)'~',
};
class JackTokenizer
{
private:
	string _file_to_process;
	unordered_map<char, int> _symbols;
	unordered_map<char, int> _whitespace;
	bool _in_comment_mode = false;

public:
	JackTokenizer(string file_name) : _file_to_process(file_name)
	{
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

		_whitespace[' '] = 1;
		_whitespace['\t'] = 1;
		_whitespace['\n'] = 1;
	}

	JackTokenizer()
	{

	}

	void load(string file_name)
	{
		_file_to_process = file_name;
	}


	string removeComments(const string& text)
	{
		string result{ text };
		int index = result.find("//");
		result = result.substr(0, index);
		for (int i = 0; result.length() > 0 && i < result.length() - 1; i++)
		{
			//cout << result[i] << result[i + 1] << endl;
			if (result[i] == '/' && result[i + 1] == '*')
			{
				_in_comment_mode = true;
				result[i] = ' ';
				result[i + 1] = ' ';
			}
			else if (result[i] == '*' && result[i + 1] == '/')
			{
				_in_comment_mode = false;
				result[i] = ' ';
				result[i + 1] = ' ';
			}
			if (_in_comment_mode == true)
			{
				result[i] = ' ';
				if (i + 2 == result.length())
				{
					result[i + 1] = ' ';
				}
			}
		}
		return result;
	}

	vector<vector<string>> processFile()
	{
		vector<vector<string>> result{};
		ifstream to_process{ _file_to_process };
		bool is_quote_mode = false;
		if (to_process.is_open() == true)
		{
			while (to_process.good() == true)
			{
				string line;
				getline(to_process, line);
				line = removeComments(line);

				istringstream input{ line };
				vector<string> current_line{};
				while (input.good() == true)
				{
					string next;
					getline(input, next);
					if (next.length() > 0)
					{
						//it's possible to have identifiers (and maybe keywords) mixed with symbols, e.g. class foo{
						//we need to separate these out into their own tokens
						istringstream text{ next };
						ostringstream current{};
						while (text.good() == true)
						{
							char ch;
							if (!(text.get(ch)))
							{
								continue;
							}
							if (_symbols.find(ch) == _symbols.end())
							{
								//ignore spaces excpet when inside a string
								if (_whitespace.find(ch) != _whitespace.end() && is_quote_mode == false)
								{
									string currentStr = current.str();
									if (currentStr.length() > 0 && currentStr != " ")
									{
										current_line.push_back(currentStr);
									}
									current = ostringstream{};
									continue;
								}

								//toggle between string and identifier
								if (ch == '"')
								{
									current << ch;
									if (is_quote_mode == true)
									{
										current_line.push_back(current.str());
										current = ostringstream{};
									}

									//toggle quote mode
									is_quote_mode = !is_quote_mode;
								}
								else
								{
									current << ch;
								}
							}
							else
							{
								string currentStr = current.str();
								if (currentStr.length() > 0 && currentStr != " ")
								{
									current_line.push_back(currentStr);
								}
								current = ostringstream{};
								current_line.push_back(string{ ch });
							}
						}
						string leftover = current.str();
						if (leftover.length() > 0 && leftover != " ")
						{
							current_line.push_back(leftover);
						}
					}
				}
				if (current_line.size() > 0)
				{
					result.push_back(current_line);
				}

			}
		}

		return result;
	}
};