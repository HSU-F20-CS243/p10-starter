#pragma once
#include <queue>
#include <sstream>
#include "StatementCompiler.hpp"
#include "JackToken.hpp"

using namespace std;
class WhileCompiler : public StatementCompiler
{
public:
	virtual void compile(queue<JackToken*>& tokens, ostringstream& result)
	{

	}
};