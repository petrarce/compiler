#include <nfa.hpp>
#include <regexp_parser.hpp>
#include "global_objects.hpp"
#include "regexp_grammar.tab.hpp"
//function parses regular expression and builds respective automaton
//on success - return 0
//on failure - return -1
int regex2nfa(string& regex, enum SATOKENS& token, nfa& new_nfa){
	lex_str.inp_buf = regex;
	lex_str.cur_pos = 0;

	if(yyparse() == 0){
		new_nfa = final_nfa;
		new_nfa.set_analyse(token);
		return 0;
	} else {
		return -1;
	}

}