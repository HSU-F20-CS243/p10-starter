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

unordered_map<string, int> CompilerFactory::_user_defined_classes;

void CompilerFactory::defineUserClass(string class_name)
{
	_user_defined_classes[class_name] = 1;
}

CompilerBase* CompilerFactory::fromTerm(queue<JackToken*>& tokens)
{
	CompilerBase* result = nullptr;
	JackToken* next = tokens.front();

	if (next->keyword == Keyword::Class)
	{
		result = new ClassCompiler();
	}
	else if (next->keyword == Keyword::Static || next->keyword == Keyword::Field)
	{
		result = new ClassVariableDeclarationCompiler();
	}
	else if (
		next->keyword == Keyword::Int
		|| next->keyword == Keyword::Static
		|| next->keyword == Keyword::Boolean
		|| _user_defined_classes[next->identifier] > 0
		)
	{
		result = new ParameterListCompiler();
	}

	return result;
}