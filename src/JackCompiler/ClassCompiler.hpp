#pragma once
#include <queue>
#include <sstream>
#include "JackToken.hpp"
#include "CompilerBase.hpp"
#include "CompilerFactory.hpp"

using namespace std;
class CompilerFactory;
class ClassCompiler : public CompilerBase
{
public:
	virtual void compile(queue<JackToken*>& tokens, ostringstream& result);
};