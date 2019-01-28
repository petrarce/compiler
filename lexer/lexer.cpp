#include <vector>
#include <iostream>
#include <nfa.hpp>
#include <lexer.hpp>
#include "regexp_links.bin.hpp"

using namespace std;

opcode lexer::set_inp_str(string str)
{
	this->inp_str = str;
	return STATUS_OK;
}
string lexer::get_inp_str()
{
	return this->inp_str;
}
string lexer::get_cur_token_val()
{
	return this->cur_token_val;
}

uint32_t lexer::get_next_token()
{
	SATOKENS token = (SATOKENS)0;
	analyse_map_s* analyse_next = NULL;
	uint32_t res = 0;

	do{
		delete analyse_next;
		analyse_next = NULL;
		analyse_next = this->prod_nfa.nfa_bt_next(this->inp_str);
		if(!analyse_next){
			return (yytokentype)0;
		}
		token = analyse_next->analyse;
	}while(token == COMMENT || token == DELIMITER);

	assert(analyse_next);
	this->cur_token_val = analyse_next->analysed_str;

	switch(analyse_next->analyse){
		case ID:
			res = Id;
			break;
		case TYPE:
			res = Type;
			break;
		case IF:
			res = If;
			break;
		case ELSE:
			res = Else;
			break;
		case WHILE:
			res = While;
			break;
		case SPECIAL:
			res = this->cur_token_val[0];
			break;
		case OPERATOR:
			res = this->cur_token_val[0];
			break;
		case LITERAL:
			res = Literal;
			break;
		case REGEXP:
			assert(0);
		default:
			assert(0);
	}

	delete analyse_next;
	//should not reach here never;
	return res;
}


lexer::lexer(string inp){
	prod_nfa.link_state(regexp_links);
	for(const pair<uint32_t, uint32_t> st_accepting : regexp_analyse){
		prod_nfa.set_accepting(st_accepting.first, (SATOKENS)st_accepting.second);
	}

	set_inp_str(inp);
}

lexer::~lexer()
{

}