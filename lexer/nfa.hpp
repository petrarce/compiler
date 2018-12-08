#pragma once

#include "state.hpp"
#include <cstdint>
#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct tr_res_s
{
	uint32_t state_count;
	uint32_t* states;
}tr_res_t;

class nfa
{
private:
	char alphabet[256];


	uint32_t states_count;
	state_c* states;

	uint32_t cur_state;

	uint8_t accepted;
private:

	opcode init_tr_result(tr_res_t& tr);
	opcode deinit_tr_res(tr_res_t& tr);

	opcode transition_f(uint32_t state, char* str);
	tr_res_t transition_get_next_states(uint32_t state, uint8_t symb);
public:
	opcode link_state(uint32_t state1, char symb, uint32_t state2);
	opcode set_accepting(uint32_t state);
	
	uint8_t nfa_run(char*);
	opcode nfa_reset();

	nfa(uint32_t states_count, char* alphabet);
	~nfa();

};

class alph_ex : exception
{
public:
	void print_ex(char* err_str)	{cout << "ALPHABET_FAILURE:" << err_str << endl;}
};
class inv_arg_ex : exception
{
public:

	void print_ex(char* err_str)	{cout << "INVALID ARGUMENT:" << err_str << endl;}
};
class empty_str_ex: exception
{
public:
	void print_ex(char* err_str)	{cout << "STRING IS EMPTY:" << err_str << endl;}

};

