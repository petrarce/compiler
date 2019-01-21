#include <stdio.h>
#include <types.hpp>
#include <lexer.hpp>
#include <lexer_regexps.hpp>
#include "regexp_links.bin.hpp"

int main(int argc, char** argv)
{
	assert(argc == 2);
	string inp = argv[1];

	lexer lexer_linked(regexp_vec, regexp_analysis);
	lexer_linked.prod_nfa.nfa_bt_run(inp, la_str, vector<uint32_t>());

	vector<uint32_t> accepting_states = lexer_linked.prod_nfa.get_accepting();
	for(uint32_t id : accepting_states){
		printf("%d, ", id);
	}
	printf("\n");

	return 0;
}