#pragma once
#include <cstdint>
#include <cerrno>
#include <string>

typedef struct trans_table_s trans_table_t;

typedef enum opcode
{
	STATUS_OK,
	STATUS_NOK,
	STATUS_ALREADY_EXISTS,
	STATUS_INVALID_ARG,
	STATUS_NO_ENTRY,
	STATUS_ALLOC_FAILED,
	STATUS_STRING_IS_EMPTY
} opcode_e;

class state_c
{
public:
	uint8_t is_accepting;
	uint32_t analyse;
	trans_table_t* transition_table[256];

	opcode_e transition_table_add_new_entry(uint8_t, state_c*, int);
	opcode_e transition_table_append_entry(uint8_t symb, state_c &state);


public:
	opcode_e transition_table_add_entry(uint8_t, state_c &);
	trans_table_s* transition_table_do_transition(uint8_t, state_c &);

	state_c();
	~state_c();
};

struct trans_table_s
{
	uint8_t symb;
	int state_count;
	state_c **states;

};

