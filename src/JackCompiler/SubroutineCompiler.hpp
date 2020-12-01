#pragma once
#include <queue>
#include <sstream>
#include "JackToken.hpp"
#include "CompilerBase.hpp"
#include "ParameterListCompiler.hpp"
#include "VariableDeclarationCompiler.hpp"
#include "StatementCompiler.hpp"

using namespace std;
class SubroutineCompiler : public CompilerBase
{
public:
	virtual void compile(queue<JackToken*>& tokens, ostringstream& result);
};