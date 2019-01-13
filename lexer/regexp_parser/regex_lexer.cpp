#include "regex_lexer.hpp"
#include <iostream>
#include <assert.h>
#include <string>

using namespace std;

int yylex()
{
	lex_str.cur_pos++;
	return lex_str.inp_buf[lex_str.cur_pos - 1];	
}

int yyerror(string str)
{
	cout << "ERROR: " << str << "\n" << endl;
	return 0;
}

