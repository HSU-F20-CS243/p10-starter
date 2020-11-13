#include "CompilerFactory.hpp"
#include "ClassCompiler.hpp"
#include "ClassVariableDeclarationCompiler.hpp"
#include "SubroutineCompiler.hpp"
#include "ParameterListCompiler.hpp"
#include "VariableDeclarationCompiler.hpp"
#include "StatementCompiler.hpp"
#include "DoCompiler.hpp"
#include "LetCompiler.hpp"
#include "WhileCompiler.hpp"
#include "ReturnCompiler.hpp"
#include "IfCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "TermCompiler.hpp"
#include "ExpressionListCompiler.hpp"

CompilerBase* CompilerFactory::fromTerm(queue<JackToken*>& tokens)
{
	CompilerBase* result = nullptr;
	JackToken* next = tokens.front();

	switch (next->keyword)
	{
	case Keyword::Class:
		result = new ClassCompiler();
		break;

		//TODO: fill in other keywords as necessary so that 
		//the factory can determine which compiler object to create

	default:
		break;
	}

	return result;
}