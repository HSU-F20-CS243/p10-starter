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
	virtual void compile(queue<JackToken*>& tokens, ostringstream& result)
	{
		result << "<subroutineDec>" << endl;

		//first token is subroutine type
		JackToken* next = tokens.front();
		tokens.pop();
		result << next->toString() << endl;

		//followed by return type
		next = tokens.front();
		tokens.pop();
		result << next->toString() << endl;

		//then subroutine name
		next = tokens.front();
		tokens.pop();
		result << next->toString() << endl;

		//open parenthesis
		next = tokens.front();
		tokens.pop();
		result << next->toString() << endl;

		//parameter list
		ParameterListCompiler pcl{};
		pcl.compile(tokens, result);

		//closed parenthesis
		next = tokens.front();
		tokens.pop();
		result << next->toString() << endl;

		//subroutine body 
		result << "<subroutineBody>" << endl;

		//open brace
		next = tokens.front();
		tokens.pop();
		result << next->toString() << endl;

		//zero or more variable declarations
		//(DataType)variable, e.g. int foo = (int)bar;
		VariableDeclarationCompiler* var_dec = dynamic_cast<VariableDeclarationCompiler*>(CompilerFactory::fromTerm(tokens));
		while (var_dec != nullptr)
		{
			var_dec->compile(tokens, result);
			delete var_dec;
			var_dec = dynamic_cast<VariableDeclarationCompiler*>(CompilerFactory::fromTerm(tokens));
		}

		//zero or more statements
		StatementCompiler* statement = dynamic_cast<StatementCompiler*>(CompilerFactory::fromTerm(tokens));
		while (statement != nullptr)
		{
			statement->compile(tokens, result);
			delete statement;
			statement = dynamic_cast<StatementCompiler*>(CompilerFactory::fromTerm(tokens));
		}


		//subroutine body -- closed brace
		next = tokens.front();
		tokens.pop();
		result << next->toString() << endl;
		result << "</subroutineBody>" << endl;

		result << "</subroutineDec>" << endl;
	}
};