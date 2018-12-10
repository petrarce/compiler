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
	string comment_atomaton = "0@@1;0@@8;0@@11;"												  			  //powerset
							  "1@/@2;2@*@3;3@qwertyuiopasdfghjklzxcvbnm_01234567890 @4;4@@3;3@@5;4@@5;5@*@6;6@/@7;" 			  												  //comments
							  "8@qwertyuiopasdfghjklzxcvbnm_@9;9@qwertyuiopasdfghjklzxcvbnm@10;10@qwertyuiopasdfghjklzxcvbnm_01234567890@10;"/*identifiers*/
							  "11@ \n\t@12;12@ \t\n@13;" /*delimiters*/;	          
	if(argc != 2)
		return -1;
	string inp_str(argv[1]);
	nfa new_nfa(14, alph);
	new_nfa.link_state(comment_atomaton);
	new_nfa.set_accepting(7, "COMMENT");
	new_nfa.set_accepting(9, "ID");
	new_nfa.set_accepting(10, "ID");
	new_nfa.set_accepting(12, "DELIM");
	new_nfa.set_accepting(13, "DELIM");
	try{
		uint8_t st;
		new_nfa.nfa_bt_run(inp_str);
	}
	catch(exception& e){
		cout << "EXITING DUE TO PREVIOUS EXCEPTIONS" << endl;
		res = -1;
	}

	cout << "finishing" << endl;

	return res;
}