#pragma once
#include <queue>
#include <sstream>
#include "CompilerBase.hpp"
#include "JackToken.hpp"

using namespace std;
class WhileCompiler : public CompilerBase
{
public:
	virtual void compile(queue<JackToken*>& tokens, ostringstream& result)
	{

	}
};