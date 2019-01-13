#include <vector>
#include <iostream>
#include <nfa.hpp>
#include <regexp_parser.hpp>
#include "lexer.hpp"

using namespace std;

lexer::lexer(vector<string> regex_vec){
	nfa tmp_nfa;
	for(string s : regex_vec){
		if(regex2nfa(s, tmp_nfa) != 0){
			printf("invalid regexp was given: %s", s);
			break;
		}
		this->prod_nfa = nfa::nfa_convert_union(this->prod_nfa ,tmp_nfa);
	}
}
lexer::~lexer(){}