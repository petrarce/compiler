#include <vector>
#include <iostream>
#include <nfa.hpp>
#include <lexer.hpp>
#include "regexp_links.bin.hpp"

using namespace std;

lexer *lexer::instance = NULL;

lexer* lexer::get_instance()
{
	if(!instance){
		instance = new lexer();
	}
	return instance;
}
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
	size_t size;

	//input was fully parsed - return finish

	do{
		delete analyse_next;
		analyse_next = NULL;

		//end of string achived - finish lexic analyse
		if(!this->inp_str.size()){
			return (yytokentype)0;
		}

		analyse_next = this->prod_nfa.nfa_bt_next(this->inp_str);
		if(!analyse_next){
			printf("LEXER ERROR:\n size=%d this->inp_str.size()=%d %s\n", size, this->inp_str.size(), this->inp_str.data());
			return (yytokentype)256;
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
		case OPEREQ:
			res = Eq;
			break;
		case OPERNEQ:
			res = Neq;
			break;
		case OPERAND:
			//TODO: init all folowwing operators after creating links to them in parser
		case OPEROR:
		case OPERINC:
		case OPERDEC:
		case REGEXP:
		default:
			printf("ERROR: analyse_next->analyse=%s\n%s\n", la_str[analyse_next->analyse].data(),
															this->cur_token_val.data());
			assert(0);
	}

	delete analyse_next;
	//should not reach here never;
	return res;
}

lexer::lexer()
{
	prod_nfa.link_state(regexp_links);
	for(const pair<uint32_t, uint32_t> st_accepting : regexp_analyse){
		prod_nfa.set_accepting(st_accepting.first, (SATOKENS)st_accepting.second);
	}
}

lexer::lexer(string inp){
	lexer();
	set_inp_str(inp);
}


lexer::~lexer()
{
	delete instance;
}