#include <state.hpp>
#include <nfa.hpp>
#include <cstdio>
#include <cstring>
#include <types.hpp>

enum {
	a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t
};

#define a_z "qwertyuiopasdfghjklzxcvbnm_"
#define A_Z "QWERTYUIOPASDFGHJKLZXCVBNM"
#define NUM "0123456789"
#define DELIM "\n\t "
#define SPEC "[]{}()=+-*^'%,.:"




int main(int argc, char** argv)
{

	int res;
	char* alph = a_z A_Z NUM DELIM ;
	const string strX = "abcd";
	if(argc != 2)
		return -1;
	string inp_str(argv[1]);
	string comment_atomaton = "0@@1\\0@@8\\0@@11\\0@@17\\0@@22\\0@@26\\0@@31\\0@@33\\0@@35\\0@@37\\0@@39\\0@@41\\"
								"0@@43\\0@@48\\0@@51\\0@@54\\0@@57\\0@@60\\0@@62\\0@@64\\0@@67\\0@@69\\0@@73\\"
							/*comments multistring*/
							  "1@/@2\\2@*@3\\3@"a_z A_Z NUM DELIM SPEC"@4\\4@@3\\3@@5\\4@@5\\5@*@6\\6@/@7\\"
  							/*keywords*/
							  "8@i@9\\9@f@10\\"
							  "11@w@12\\12@h@13\\13@i@14\\14@l@15\\15@e@16\\"
							  "17@e@18\\18@l@19\\19@s@20\\20@e@21\\"
							/*types*/
							  "22@i@23\\23@n@24\\24@t@25\\"
							  "26@r@27\\27@e@28\\28@a@29\\29@l@30\\"
							//specoal symbols:
							  "31@(@32\\"
							  "33@)@34\\"
							  "35@{@36\\"
							  "37@}@38\\"
							  "39@=@40\\"
							  "41@;@42\\"
							//operators
							  "43@><!~@47\\"
							  "48@=@49\\49@=@50\\"
							  "51@<@52\\52@=@53\\"
							  "54@=@55\\55@<@56\\"
							  "57@>@58\\58@=@59\\"
							  "60@+-*/%@61\\"
							/*identifiers*/
							  "62@"a_z A_Z"@63\\63@"a_z A_Z NUM"@63\\"
							//oneline comment
							  "64@/@65\\65@/@66\\66@"a_z A_Z SPEC NUM "\t ""@66\\"
							/*delimiters*/
							  "67@"DELIM"@68\\68@"DELIM"@68\\"
							/*literals*/
							  "69@"NUM"@70\\70@"NUM"@70\\70@.@71\\71@"NUM"@72\\72@"NUM"@72\\"
							  "73@\"@74\\74@"a_z A_Z " \t" NUM SPEC"@75\\75@"a_z A_Z " \t" NUM SPEC"@75\\75@\"@76\\" ;


	nfa new_nfa;
	new_nfa.link_state(comment_atomaton);
	new_nfa.set_accepting({7,66}, COMMENT);
	new_nfa.set_accepting(63, ID);
	new_nfa.set_accepting(68, DELIMITER);
	new_nfa.set_accepting({25,30}, TYPE);
	new_nfa.set_accepting({10,16,21}, KEYWORD);
	new_nfa.set_accepting({32,34,36,38,40,42}, SPECIAL);
	new_nfa.set_accepting({47,50,53,56,59,61}, OPERATOR);
	new_nfa.set_accepting({70, 71, 72, 76}, LITERAL);


	try{
		uint8_t st;
		new_nfa.nfa_bt_run(inp_str, la_str, {DELIMITER});

	}
	catch(exception& e){
		cout << "EXITING DUE TO PREVIOUS EXCEPTIONS" << endl;
		res = -1;
	}

	cout << "finishing" << endl;

	return res;
}