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

bool CompilerFactory::isTerm(JackToken* token)
{
	return false;
}

void CompilerFactory::defineUserClass(string class_name)
{
	_user_defined_classes[class_name] = 1;
}

bool CompilerFactory::isUserDefinedClass(string class_name)
{
	return _user_defined_classes[class_name] == 1;
}

bool CompilerFactory::isType(JackToken* token)
{
	return token->keyword == Keyword::Int || token->keyword == Keyword::Static || token->keyword == Keyword::Boolean || CompilerFactory::isUserDefinedClass(token->rawText);
}

CompilerBase* CompilerFactory::fromTerm(queue<JackToken*>& tokens)
{
	CompilerBase* result = nullptr;
	JackToken* next = tokens.front();

	//class
	if (next->keyword == Keyword::Class)
	{
		result = new ClassCompiler();
	}

	//class variable declaration
	else if (next->keyword == Keyword::Static || next->keyword == Keyword::Field)
	{
		result = new ClassVariableDeclarationCompiler();
	}

	//subroutine declaration
	else if (next->keyword == Keyword::Constructor || next->keyword == Keyword::Function || next->keyword == Keyword::Method)
	{
		result = new SubroutineCompiler();
	}

	//variable declaration
	else if (next->keyword == Keyword::Var)
	{
		result = new VariableDeclarationCompiler();
	}

	//let statement
	else if (next->keyword == Keyword::Let)
	{
		result = new LetCompiler();
	}

	//if statement
	else if (next->keyword == Keyword::If)
	{
		result = new IfCompiler();
	}

	//while statement
	else if (next->keyword == Keyword::While)
	{
		result = new WhileCompiler();
	}

	//do
	else if (next->keyword == Keyword::Do)
	{
		result = new DoCompiler();
	}

	//return
	else if (next->keyword == Keyword::Return)
	{
		result = new ReturnCompiler();
	}



	return result;
}