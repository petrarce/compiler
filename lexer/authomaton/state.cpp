#include "state.hpp"
#include <cstdlib>
#include <cstring>

using namespace std;

opcode_e 		state_c::transition_table_add_new_entry(uint8_t symb, state_c *states, int state_count)
{
	if(this->transition_table[symb])
		return STATUS_ALREADY_EXISTS;
	if(!states)
		return STATUS_INVALID_ARG;
	this->transition_table[symb] = new trans_table_t;
	this->transition_table[symb]->symb = symb;
	this->transition_table[symb]->state_count = state_count;
	this->transition_table[symb]->states = (state_c**)malloc( sizeof(state_c*) * state_count);
	for(int i = 0; i < state_count; i++)
		this->transition_table[symb]->states[i] = states + i;

	return STATUS_OK;

}
opcode_e 		state_c::transition_table_append_entry(uint8_t symb, state_c &state)
{
	state_c **ptr;

	if(!this->transition_table[symb])
		return transition_table_add_new_entry(symb, &state, 1);

	ptr = (state_c**)malloc(sizeof(state_c*) * (this->transition_table[symb]->state_count + 1));
	if(!ptr)
		return STATUS_ALLOC_FAILED;
	memcpy(ptr, this->transition_table[symb]->states, this->transition_table[symb]->state_count*(sizeof(state_c*)));
	free(this->transition_table[symb]->states);
	this->transition_table[symb]->states = ptr;
	this->transition_table[symb]->states[this->transition_table[symb]->state_count] = &state;
	this->transition_table[symb]->state_count++;

	return STATUS_OK;
}

opcode_e 		state_c::transition_table_add_entry(uint8_t symb, state_c &state)
{
	return transition_table_append_entry(symb, state);
}

trans_table_s* 	state_c::transition_table_do_transition(uint8_t symb, state_c &state)
{
	if(!state.transition_table[symb]){
		errno = STATUS_INVALID_ARG;
		return 0;
	}
	return state.transition_table[symb];
}

state_c::state_c()
{
	is_accepting = 0;
	memset(transition_table, 0, sizeof(transition_table));
}

state_c::~state_c()
{
	for(int i = 0; i < 256; i++){
		if(!this->transition_table[i])
			continue;
		free(this->transition_table[i]->states);
		delete this->transition_table[i];
	}
}