#include <state.hpp>
#include <nfa.hpp>
#include <cstdio>
#include <cstring>

int main(int argc, char** argv)
{

	int res;
	nfa new_nfa(5, "ab");
	new_nfa.link_state(0, 'a', 1);
	new_nfa.link_state(1, 'b', 2);
	new_nfa.link_state(0, 'a', 3);
	new_nfa.link_state(3, 'a', 4);
	new_nfa.set_accepting(4);
	new_nfa.set_accepting(2);


	try{
		uint8_t st = new_nfa.nfa_run((argc == 2 && strlen(argv[1]))?argv[1]:NULL);
		printf("%s, is %s\n", argv[1], (st)?"accepted":"denied");
	}
	catch(exception& e){
		cout << "EXITING DUE TO PREVIOUS EXCEPTIONS" << endl;
		res = -1;
	}

	cout << "finishing" << endl;

	return res;
}