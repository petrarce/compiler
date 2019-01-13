//here will be implemented lexer class
#pragma once
#include <vector>
#include <nfa.hpp>

using namespace std;

class lexer
{
public:
	nfa prod_nfa;
public:
	lexer(vector<string> regex_vec);
	~lexer();
};