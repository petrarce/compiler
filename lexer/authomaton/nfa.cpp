#include <nfa.hpp>
#include <string>
#include <cstring>
#include <algorithm>

class inv_arg_ex inv_arg_ex_obj;
class empty_str_ex empty_str_ex_obj;

static void my_set_union(vector<uint32_t>& dest, vector<uint32_t> src)
{
	uint8_t st1_is_in_set = 0;

	if(!dest.size()){
		dest = src;
		return;
	}

	for(uint32_t st1 : src){
		for(uint32_t st2 : dest){
			if(st1 == st2){
				st1_is_in_set = 1;
				break;
			}
		}

		if(!st1_is_in_set)
			dest.push_back(st1);
		else
			st1_is_in_set = 0;
	}
	return;
}


opcode nfa::init_cur_state_list()
{
	this->cur_state_list.clear();
	cur_state_list.push_back(0);
}

opcode nfa::deinit_cur_state_list()
{
	this->cur_state_list.clear();
}


vector<uint32_t> nfa::transition_get_next_states(uint32_t state, uint8_t symb)
{
	vector<uint32_t> 	states_id;

	if(!this->states[state].transition_table[symb])
		return states_id;

	state_c** 			states = this->states[state].transition_table[symb]->states;
	auto 				state_count = this->states[state].transition_table[symb]->state_count;

	//in transition table can be empty at this point (means, that any further transition leads to dead state)
	if(!this->states[state].transition_table[symb])
		return states_id;

	for(uint32_t  i = 0; i < this->states_count; i++){
		for(uint32_t j = 0; j < state_count; j++){
			if(states[j] == this->states + i){
				states_id.push_back(i);
			}
		}
	}

	return states_id;
}

opcode nfa::link_state(uint32_t state1, char symb, uint32_t state2)
{
	opcode status;
	status = states[state1].transition_table_add_entry(symb, states[state2]);
	return status;
}

opcode nfa::link_state(uint32_t state1, char* symbs, uint32_t state2)
{
	opcode status;
	size_t symb_sz = strlen(symbs);
	for(int i = 0; i < symb_sz; i++)
		link_state(state1, symbs[i], state2);

	return status;
}


void nfa::nfa_run(string str)
{
	int32_t res = 0;
	opcode status;
	try{
		if(!str.size())
			throw empty_str_ex_obj;
		status = nfa_reset();
		for(char c : str)
			nfa_next(c);
	}
	catch(empty_str_ex& e)
	{
		e.print_ex("currently string is empty");
		throw exception();
	}

}

uint8_t nfa::nfa_status()
{
	for(uint32_t state : this->cur_state_list){
		if (this->states[state].is_accepting)
			return 1;
	}
	return 0;

}


void nfa::nfa_next(char symb)
{
	vector<uint32_t> new_cur_state_list;

	for (uint32_t state : this->cur_state_list){
		vector<uint32_t> tmp_states = transition_get_next_states(state, symb);
		vector<uint32_t> tmp_states_eps = transition_get_next_states(state, EPS);
		
		my_set_union(tmp_states, tmp_states_eps);

		my_set_union(new_cur_state_list, tmp_states);
	}
	this->cur_state_list = new_cur_state_list;
}

opcode nfa::nfa_reset()
{
	init_cur_state_list();	
	return STATUS_OK;
}

opcode nfa::set_accepting(uint32_t state)
{
	this->states[state].is_accepting = true;
	return STATUS_OK;
}

nfa::nfa(uint32_t states_count, char* alphabet)
{
	memset(this->alphabet, 0, sizeof(this->alphabet));
	for(int i = 0; i < strlen(alphabet); i++)
		this->alphabet[alphabet[i]] = alphabet[i];
	this->states = new state_c[states_count];
	this->states_count = states_count;
	init_cur_state_list();
}

nfa::~nfa(){

	delete[] this->states;
	memset(this->alphabet, 0, sizeof(this->alphabet));
	deinit_cur_state_list();
}
