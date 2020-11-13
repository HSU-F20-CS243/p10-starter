#pragma once
#include <queue>
#include <string>
#include <sstream>

#include "JackToken.hpp"
#include "CompilerFactory.hpp"
using namespace std;

class CompilerEngine
{
private:
	queue<JackToken*> _tokens;

public:
	CompilerEngine(queue<JackToken*>& tokens) : _tokens(tokens) {}
	CompilerEngine() {}
	void loadTokens(queue<JackToken*>& tokens)
	{
		_tokens = tokens;
	}

	string compile()
	{
		ostringstream result{};

		//begin compilation chain
		CompilerBase* next_command = CompilerFactory::fromTerm(_tokens);
		next_command->compile(_tokens, result);

		//always remember to clean up memory
		delete next_command;

		return result.str();

	}
};