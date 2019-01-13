#include <stdio.h>
#include <types.hpp>
#include <lexer.hpp>
#include <lexer_regexps.hpp>

int main(int argc, char** argv)
{

	lexer new_lexer(regexp_vec);
	string inp_str = argv[1];

	new_lexer.prod_nfa.nfa_bt_run(inp_str, la_str, vector<uint32_t>());

	return 0;
}