#pragma once

#include <state.hpp>
#include <types.hpp>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

#define EPS '@'

using namespace std;

typedef struct {
	string str;
	uint32_t analyse;
} analyse_map_s;

class nfa
{
private:
	vector<state_c> states; 			//states of the automaton
	vector<uint32_t> cur_state_list;	//states, which are currently active in automaton
	vector<vector<uint32_t>> bt_log;
private:

	opcode init_cur_state_list();
	opcode deinit_cur_state_list();


	opcode nfa_clause();
	vector<uint32_t>  transition_get_next_states(uint32_t , uint8_t );
	opcode nfa_bt_log_save(uint32_t state,uint32_t position);

public:
	friend void push_states_with_offset(nfa&, nfa&);

	opcode link_state(const uint32_t , const char , const uint32_t );
	opcode link_state(const uint32_t , const string& , const uint32_t );
	opcode link_state(const string&);
	string print_links();

	opcode set_accepting(uint32_t, uint32_t);
	opcode set_accepting(vector<uint32_t> , uint32_t);

	opcode set_analyse(enum SATOKENS token);

	static nfa nfa_convert_clausure(nfa& );
	static nfa nfa_convert_concat(nfa&, nfa&);
	static nfa nfa_convert_union(nfa&, nfa&);

	void nfa_next(char);
	opcode nfa_run(string&);
	analyse_map_s* nfa_bt_next(string&);
	opcode nfa_bt_run(string&, vector<string>&, vector<uint32_t>);
	uint32_t nfa_status();
	opcode nfa_reset();



	nfa();
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

