#include <regexp_parser.hpp>
#include "regex_lexer.hpp"
#include "regexp_grammar.tab.hpp"

lex_str_t lex_str;
//function parses regular expression and builds respective automaton
//on success - return 0
//on failure - return -1
int regex2nfa(string& regex, nfa& new_nfa){
	lex_str.inp_buf = regex;
	lex_str.cur_pos = 0;

	if(yyparse() == 0){
		new_nfa = final_nfa;
		return 0;
	} else {
		return -1;
	}
}
