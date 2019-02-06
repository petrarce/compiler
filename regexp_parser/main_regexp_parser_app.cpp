#include <iostream>
#include <lexer_regexps.hpp>
#include <string>
#include "regexp_parser.hpp"

using namespace std;

inline void update_progress_bar(uint32_t status, uint32_t max){
	string bar;
	uint32_t prc = (status*100)/max;

	bar += to_string(prc) + "% ";
	for(int i = 0; i < prc; i++){
		bar.push_back('#');
	}
	bar += "\r";
	fprintf(stderr ,"%s", bar.data());
	cout.flush();
}

int main(){

	nfa regexp_nfa;
	int i;
	string status_str;
	uint32_t status_prc = 0;

	//parse all regexps and convert them to nfa
	for(i = 0; i < regexp_vec.size(); i++){
		nfa tmp_nfa;
		update_progress_bar(i, regexp_vec.size());
		int status = regex2nfa(regexp_vec[i], regexp_analysis[i], tmp_nfa);
		assert(status == 0);
		regexp_nfa = nfa::nfa_convert_union(regexp_nfa, tmp_nfa);
	}
	update_progress_bar(1,1);
	fprintf(stderr, "\r\n");

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