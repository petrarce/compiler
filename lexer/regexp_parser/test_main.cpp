#include <stdio.h>
#include "lexer.hpp"
#include <regexp_grammar.tab.hpp>

lex_str_t lex_str;

int main(int argc, char** argv)
{
	lex_str.inp_buf = argv[1];
	lex_str.cur_pos = 0;
	string inp_str = argv[2];

	printf("parsing string: %s\n", argv[1]);

	printf("parser result: %d\n", yyparse());
	final_nfa.nfa_bt_run(inp_str, la_str, vector<uint32_t>());

	return 0;
}