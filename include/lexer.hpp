//here will be implemented lexer class
#pragma once
#include <vector>
#include <nfa.hpp>
#include <while_grammar.tab.hpp>

using namespace std;

class lexer
{
private:
	static lexer	*instance;
	string 			inp_str;
	string			cur_token_val;
	nfa 			prod_nfa;
public:
	static lexer* get_instance();
	opcode set_inp_str(string);
	string get_inp_str();
	string get_cur_token_val();
	uint32_t get_next_token();
private:
	lexer();
	lexer(string inp_str);
public:
	~lexer();
};