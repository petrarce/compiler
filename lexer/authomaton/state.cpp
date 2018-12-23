#include <state.hpp>
#include <cstdlib>
#include <cstring>

using namespace std;

opcode_e 		state_c::transition_table_add_new_entry(uint8_t symb, vector<uint32_t> states)
{
	if(this->transition_table[symb])
		return STATUS_ALREADY_EXISTS;
	if(!states.size())
		return STATUS_INVALID_ARG;

	this->transition_table[symb] 				= new trans_table_t;
	this->transition_table[symb]->symb 			= symb;
	this->transition_table[symb]->state_ids 	= states;

	return STATUS_OK;

}
opcode_e 		state_c::transition_table_append_entry(uint8_t symb, uint32_t state)
{
	state_c **ptr;
	vector<uint32_t> vec; vec.push_back(state);

	if(!this->transition_table[symb])
		return transition_table_add_new_entry(symb, vec);

	this->transition_table[symb]->state_ids.push_back(state);

	return STATUS_OK;
}

opcode_e 		state_c::transition_table_add_entry(uint8_t symb, uint32_t state_id)
{
	return transition_table_append_entry(symb, state_id);
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
		this->transition_table[i]->state_ids.clear();
		delete this->transition_table[i];
	}
}