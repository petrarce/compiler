#include "state.hpp"
#include "nfa.hpp"
#include <cstdio>

int main(int argc, char** argv)
{

	nfa new_nfa(5, "ab");
	new_nfa.link_state(0, 'a', 1);
	new_nfa.link_state(1, 'b', 2);
	new_nfa.link_state(0, 'a', 3);
	new_nfa.link_state(3, 'a', 4);
	new_nfa.set_accepting(4);
	new_nfa.set_accepting(2);


	uint8_t st = new_nfa.nfa_run(argv[1]);
	printf("%s, is %s\n", argv[1], (st)?"accepted":"denied");


	return 0;
}