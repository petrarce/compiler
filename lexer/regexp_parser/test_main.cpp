#include <stdio.h>
#include <regexp_parser.hpp>
#include <types.hpp>

int main(int argc, char** argv)
{

	nfa new_nfa;
	string inp_str = argv[2];

	printf("parsing string: %s\n", argv[1]);

	if(regex2nfa(argv[1], new_nfa) == 0){
		printf("regexp parsed sucessfully\n");
	} else {
		printf("failed to parse regexp\n");
		return -1;
	}
	
	new_nfa.nfa_bt_run(inp_str, la_str, vector<uint32_t>());

	return 0;
}