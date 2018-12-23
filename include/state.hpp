#pragma once
#include <cstdint>
#include <cerrno>
#include <string>
#include <vector>

using namespace std;

struct trans_table_s
{
	uint8_t symb;
	vector<uint32_t> state_ids;

};
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
	uint32_t id;
	uint8_t is_accepting;
	uint32_t analyse;
	vector<trans_table_t> transition_table;

	opcode_e transition_table_add_new_entry(uint8_t, vector<uint32_t>);
	opcode_e transition_table_append_entry(uint8_t symb, uint32_t);


public:
	opcode_e transition_table_add_entry(uint8_t, uint32_t);

	state_c();
	~state_c();
};


