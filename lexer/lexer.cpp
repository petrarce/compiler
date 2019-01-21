#include <vector>
#include <iostream>
#include <nfa.hpp>
#include <regexp_parser.hpp>
#include "regexp_links.bin.hpp"
#include "lexer.hpp"

using namespace std;

lexer::lexer(vector<string> regex_vec, vector<enum SATOKENS> tokens_vec){
	nfa tmp_nfa;
	assert(regex_vec.size() == tokens_vec.size());

	for(int i = 0; i < regex_vec.size(); i++){
		assert(regex2nfa(regex_vec[i], tokens_vec[i], tmp_nfa) == 0);
		this->prod_nfa = nfa::nfa_convert_union(this->prod_nfa ,tmp_nfa);
	}
}
lexer::lexer(){
	prod_nfa.link_state(while_nfa_links);
}
lexer::~lexer(){}