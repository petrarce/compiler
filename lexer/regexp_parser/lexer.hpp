#pragma once
#include <iostream>

using namespace std;

typedef struct {
	char* inp_buf;
	int cur_pos;
} lex_str_t;

extern lex_str_t lex_str;

int yylex();
int yyerror(string str);