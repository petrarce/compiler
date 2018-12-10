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
	char* alph = "/*qwertyuiopasdfghjklzxcvbnm_01234567890 ";
	const string strX = "abcd";
	string comment_atomaton = "0@@1;" "1@/@2;2@*@3;3@qwertyuiopasdfghjklzxcvbnm_ @4;4@@3;3@@5;4@@5;5@*@6;6@/@7;";
	/*string comment_atomaton = "0@@1;0@@8;"												  			  //powerset
							  "1@/@2;2@*@3;3@qwertyuiopasdfghjklzxcvbnm_ @4;4@@3;3@@5;4@@5;5@*@6;6@/@7;" 			  //comments
							  "8@qwertyuiopasdfghjklzxcvbnm_@9;9@qwertyuiopasdfghjklzxcvbnm_01234567890@10;10@qwertyuiopasdfghjklzxcvbnm_01234567890@10;";*/	          //identifiers*/
	if(argc != 2)
		return -1;
	string inp_str(argv[1]);
	nfa new_nfa(8, alph);
	/*new_nfa.link_state(0, '/', 1);
	new_nfa.link_state(1, '*', 2);
	new_nfa.link_state(2, strX, 3);
	new_nfa.link_state(2, EPS, 4);
	new_nfa.link_state(3, EPS, 4);
	new_nfa.link_state(3, EPS, 2);
	new_nfa.link_state(4, '*', 5);
	new_nfa.link_state(5, '/', 6);*/
	new_nfa.link_state(comment_atomaton);
	new_nfa.set_accepting(7);
	//new_nfa.set_accepting(10);



	try{
		uint8_t st;
		new_nfa.nfa_run(inp_str);
		printf("%s, is %s\n", argv[1], (new_nfa.nfa_status())?"accepted":"denied");
	}
	catch(exception& e){
		cout << "EXITING DUE TO PREVIOUS EXCEPTIONS" << endl;
		res = -1;
	}

	cout << "finishing" << endl;

	return res;
}