#include <iostream>
#include <assert.h>
#include <string>
#include "regex_lexer.hpp"
#include "global_objects.hpp"
#include "regexp_grammar.tab.hpp"


using namespace std;

lex_str_t lex_str;

int yylex()
{
	lex_str.cur_pos++;

	if(!lex_str.inp_buf[lex_str.cur_pos-1])
		return 0;

	if(lex_str.inp_buf[lex_str.cur_pos-1] == '\\'){
		//'\' is a ecranise symbol, so split 
		//this and juset return next symbol after it
		lex_str.cur_pos++;
		return ASCII;
	}

	for(char symb : regexp_special_symbs){
		if(symb == lex_str.inp_buf[lex_str.cur_pos-1])
			return symb;
	}
	
	return ASCII;	
}

int yyerror(string str)
{
	cout << "ERROR: " << str << "\n" << endl;
	return 0;
}