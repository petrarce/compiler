#pragma once
#include <iostream>
#include <string>
#include <nfa.hpp>

using namespace std;

typedef struct {
	string inp_buf;
	int cur_pos;
} lex_str_t;


int yylex();
int yyerror(string str);