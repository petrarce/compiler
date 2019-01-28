//here will be implemented lexer class
#pragma once
#include <vector>
#include <nfa.hpp>
#include <while_grammar.tab.hpp>

using namespace std;

class lexer
{
private:
	string 		inp_str;
	string		cur_token_val;
public:
	nfa prod_nfa;
public:
	opcode set_inp_str(string);
	string get_inp_str();
	string get_cur_token_val();

	uint32_t get_next_token();

	lexer(string inp_str);

	~lexer();
};