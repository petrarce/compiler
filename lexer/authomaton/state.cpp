#include <state.hpp>
#include <cstdlib>
#include <cstring>

using namespace std;

opcode 		state_c::transition_table_add_new_entry(uint8_t symb, vector<uint32_t> states)
{
	if(this->transition_table[symb].symb)
		return STATUS_ALREADY_EXISTS;
	if(!states.size())
		return STATUS_INVALID_ARG;

	this->transition_table[symb].symb 			= symb;
	this->transition_table[symb].state_ids 		= states;

	return STATUS_OK;

}
opcode 		state_c::transition_table_append_entry(uint8_t symb, uint32_t state)
{
	state_c **ptr;
	vector<uint32_t> vec; vec.push_back(state);

	if(!this->transition_table[symb].symb)
		return transition_table_add_new_entry(symb, vec);

	this->transition_table[symb].state_ids.push_back(state);

	return STATUS_OK;
}

opcode 		state_c::transition_table_add_entry(uint8_t symb, uint32_t state_id)
{
	return transition_table_append_entry(symb, state_id);
}

state_c::state_c()
{
	is_accepting = 0;
	transition_table.resize(256);
	for(uint32_t i = 0; i < transition_table.size(); i++){
		transition_table[i].symb = 0;
	}
}

state_c::~state_c()
{
	for(int i = 0; i < 256; i++){
		if(!this->transition_table[i].symb)
			continue;
		this->transition_table[i].state_ids.clear();
	}
}