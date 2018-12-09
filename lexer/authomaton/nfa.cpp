#include <nfa.hpp>
#include <string>
#include <cstring>

class inv_arg_ex inv_arg_ex_obj;
class empty_str_ex empty_str_ex_obj;

inline opcode nfa::deinit_tr_res(tr_res_t& tr)
{
	free(tr.states);
	tr.states = 0;

	return STATUS_OK;
}
inline opcode nfa::init_tr_result(tr_res_t& tr)
{
	if(tr.states)
		deinit_tr_res(tr);
	
	tr.states = (uint32_t*)malloc(sizeof(*tr.states) * this->states_count);

	if(!tr.states)
		return STATUS_ALLOC_FAILED;
	memset(tr.states, 0, sizeof(*tr.states) * this->states_count);
	return STATUS_OK;
}

tr_res_t nfa::transition_get_next_states(uint32_t state, uint8_t symb)
{
	tr_res_t tr;
	tr.states = NULL;
	tr.state_count = 0;

	//in transition table can be empty at this point (means, that any further transition leads to dead state)
	if(!this->states[state].transition_table[symb])
		return tr;
	auto state_count = this->states[state].transition_table[symb]->state_count;
	state_c** states = this->states[state].transition_table[symb]->states;



	init_tr_result(tr);
	for(int i = 0; i < this->states_count; i++){
		for(int j = 0; j < state_count; j++){
			if(states[j] == this->states + i){
				tr.states[tr.state_count] = i;
				tr.state_count++;
			}
		}
	}

	return tr;
}

opcode nfa::goto_next_transitions(tr_res_t& tr_list, char* str){
	opcode status;

	for(int i = 0; i < tr_list.state_count; i++){
		status = transition_f(tr_list.states[i], str);

		if(STATUS_INVALID_ARG == status){
			throw inv_arg_ex_obj;
		}

		if(STATUS_STRING_IS_EMPTY == status){

			if(this->accepted){
				break;
			}
		}
	}
	return status;
}

opcode nfa::transition_f(uint32_t state, char* str)
{
	opcode status;
	if(!str){
		return STATUS_INVALID_ARG;
	}

	if(!str[0]){
		if(this->states[state].is_accepting){
			this->accepted = true;
			this->cur_state = state;
		}
		return STATUS_STRING_IS_EMPTY;
	}

	try{
		tr_res_t tr_list = transition_get_next_states(state, str[0]);
		status = goto_next_transitions(tr_list, str+1);
		//if not matched any of previous paterns try to make eps transition
		if(!this->states[this->cur_state].is_accepting){
			deinit_tr_res(tr_list);
			tr_list = transition_get_next_states(state, '@');
			status = goto_next_transitions(tr_list, str);
		}
		deinit_tr_res(tr_list);
	}
	catch (inv_arg_ex& e){
		e.print_ex("invalid argument was received");
		status = STATUS_INVALID_ARG;

	}
	return status;
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


uint8_t nfa::nfa_run(char* str)
{
	uint8_t res = 0;
	opcode status;
	try{
		if(!str)
			throw empty_str_ex_obj;
		status = nfa_reset();
		status = transition_f(this->cur_state, str);
		if(this->accepted)
			res = 1;
		else
			res = 0;
	}
	catch(empty_str_ex& e)
	{
		e.print_ex("currently string is empty");
		throw exception();
	}

	return res;
}

opcode nfa::nfa_reset()
{
	this->cur_state = 0;
	this->accepted = false;
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
	this->accepted = 0;
	this->cur_state = 0;
}

nfa::~nfa(){

	delete[] this->states;
	memset(this->alphabet, 0, sizeof(this->alphabet));
}
