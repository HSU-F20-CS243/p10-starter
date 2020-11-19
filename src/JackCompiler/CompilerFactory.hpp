#pragma once
#include "JackToken.hpp"
#include "CompilerBase.hpp"

#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

class CompilerFactory
{
private:
	static unordered_map<string, int> _user_defined_classes;
public:

	static void defineUserClass(string class_name);
	static CompilerBase* fromTerm(queue<JackToken*>& tokens);
};