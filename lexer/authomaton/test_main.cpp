#include <state.hpp>
#include <nfa.hpp>
#include <cstdio>
#include <cstring>

enum {
	a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t
};
#define X "abcd"

int main(int argc, char** argv)
{

	int res;
	char* alph = "/*abcd";
	nfa new_nfa(7, alph);
	new_nfa.link_state(0, '/', 1);
	new_nfa.link_state(1, '*', 2);
	new_nfa.link_state(2, X, 3);
	new_nfa.link_state(2, EPS, 4);
	new_nfa.link_state(3, EPS, 4);
	new_nfa.link_state(3, EPS, 2);
	new_nfa.link_state(4, '*', 5);
	new_nfa.link_state(5, '/', 6);
	new_nfa.set_accepting(6);


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