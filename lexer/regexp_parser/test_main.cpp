#include <stdio.h>
#include "lexer.hpp"
#include <regexp_grammar.tab.hpp>

lex_str_t lex_str;

int main(int argc, char** argv)
{
	lex_str.inp_buf = argv[1];
	lex_str.cur_pos = 0;

	printf("parsing string: %s\n", argv[1]);

	printf("parser result: %d\n", yyparse());
	return 0;
}