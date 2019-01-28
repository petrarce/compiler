#include <iostream>
#include <lexer_regexps.hpp>
#include "regexp_parser.hpp"

using namespace std;

int main(){

	nfa regexp_nfa;
	int i;

	//parse all regexps and convert them to nfa
	for(i = 0; i < regexp_vec.size(); i++){
		nfa tmp_nfa;
		int status = regex2nfa(regexp_vec[i], regexp_analysis[i], tmp_nfa);
		assert(status == 0);
		regexp_nfa = nfa::nfa_convert_union(regexp_nfa, tmp_nfa);
	}

	string links = regexp_nfa.get_links();
	auto accepting = regexp_nfa.get_accepting();

	printf("#include <vector>\n");
	printf("const string regexp_links = {\n\t", links[i]);
	for(i = 0; i < links.size()-1; i++){
		if(!(i%8) && i != 0){
			printf("0x%x,\n\t", links[i]);
			continue;
		}
		printf("0x%x, ", links[i]);
	}
	printf("0x%x\n};\n", links[i]);

	printf("const vector<pair<uint32_t, uint32_t>> regexp_analyse = {\n");
	for(i = 0; i < accepting.size()-1; i++){
		printf("\t{%d, %d},\n", accepting[i].first, accepting[i].second);
	}
	printf("\t{%d, %d}\n};", accepting[i].first, accepting[i].second);
	printf("\n");
}