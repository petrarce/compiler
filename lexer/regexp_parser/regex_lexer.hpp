#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef struct {
	string inp_buf;
	int cur_pos;
} lex_str_t;

extern lex_str_t lex_str;

int yylex();
int yyerror(string str);