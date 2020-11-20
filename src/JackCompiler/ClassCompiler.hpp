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
	virtual void compile(queue<JackToken*>& tokens, ostringstream& result)
	{
		//open XML tag
		result << "<class>" << endl;

		//first item should be class keyword
		JackToken* next = tokens.front();
		tokens.pop();
		result << next->toString() << endl;

		//next item should be class identifier
		next = tokens.front();
		tokens.pop();
		result << next->toString() << endl;

		//add user defined class to the factory's list of known classes
		CompilerFactory::defineUserClass(next->identifier);

		//then a curly brace
		next = tokens.front();
		tokens.pop();
		result << next->toString() << endl;

		//AC Note: a good compiler should check to see if what comes next is expected.  In the case of
		//a class, we should expect zero or more ClassVariableDeclarations followed by zero or more Subroutines.
		//Right now, this isn't happening -- I'm just taking whatever the factory gives me.
		CompilerBase* nextCompiler = CompilerFactory::fromTerm(tokens);
		nextCompiler->compile(tokens, result);
		delete nextCompiler;

		//close curly
		next = tokens.front();
		tokens.pop();
		result << next->toString() << endl;

		//close class tag
		result << "</class>" << endl;
	}
};