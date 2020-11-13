#pragma once
#include "JackToken.hpp"
#include "CompilerBase.hpp"

#include <queue>
using namespace std;

class CompilerFactory
{
public:
	static CompilerBase* fromTerm(queue<JackToken*>& tokens);
};