#pragma once
#include <queue>
#include <sstream>
#include "JackToken.hpp"
#include "StatementCompiler.hpp"

using namespace std;
class LetCompiler : public StatementCompiler
{
public:
	virtual void compile(queue<JackToken*>& tokens, ostringstream& result)
	{

	}
};