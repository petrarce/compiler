#pragma once

#include "state.hpp"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

#define EPS '@'

using namespace std;

class nfa
{
private:
	char alphabet[256];
	uint32_t states_count;
	state_c* states;
	vector<uint32_t> cur_state_list;
private:

	opcode init_cur_state_list();
	opcode deinit_cur_state_list();


	opcode goto_next_transitions(vector<uint32_t> &, char*);
	opcode transition_f(uint32_t , char* );
	vector<uint32_t>  transition_get_next_states(uint32_t , uint8_t );
public:
	opcode link_state(uint32_t , char , uint32_t );
	opcode link_state(uint32_t , char* , uint32_t );
	opcode set_accepting(uint32_t );
	
	void nfa_next(char);
	void nfa_run(string);
	uint8_t nfa_status();
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

