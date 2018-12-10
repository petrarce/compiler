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
	vector<vector<uint32_t>> bt_log;
	string delimiters;
private:

	opcode init_cur_state_list();
	opcode deinit_cur_state_list();


	void nfa_clause();
	vector<uint32_t>  transition_get_next_states(uint32_t , uint8_t );
	void nfa_bt_log_save(uint32_t state,uint32_t position);
public:
	opcode link_state(uint32_t , char , uint32_t );
	opcode link_state(uint32_t , string& , uint32_t );
	opcode link_state(string&);

	opcode set_accepting(uint32_t, string);
	opcode set_accepting(vector<uint32_t> , string);

	void nfa_next(char);
	void nfa_run(string&);
	opcode nfa_bt_next(string&);
	opcode nfa_bt_run(string&);
	uint32_t nfa_status();
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

