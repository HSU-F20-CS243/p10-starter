#pragma once
#include <queue>
#include <sstream>
#include "JackToken.hpp"

using namespace std;

class CompilerBase
{
public:
	virtual void compile(queue<JackToken*>& tokens, ostringstream& result) = 0;

};