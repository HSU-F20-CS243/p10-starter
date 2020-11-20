#pragma once
#include <queue>
#include <sstream>
#include "JackToken.hpp"
#include "CompilerBase.hpp"

using namespace std;
class ReturnCompiler : public StatementCompiler
{
public:
	virtual void compile(queue<JackToken*>& tokens, ostringstream& result)
	{

	}
};