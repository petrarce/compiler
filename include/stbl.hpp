#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <types.hpp>

using namespace std;
class stbl_entry{
public:
	string id;
	string type;
	stbl_entry* next;
	//adds new entry to the end of the list
	opcode set_last(stbl_entry*);
	stbl_entry(string id, string type){ 
		this->id = id; 
		this->type = type;
		this->next = NULL;
	};
	~stbl_entry(){};
};

class stbl{
private:
	vector<stbl_entry*> buckets;
	uint32_t calc_hash(string id);
	opcode clean_buckets();
public:
	//Creates new entry with id and type and adds it to a bucket
	opcode add_entry(string id, string type);
	//Removes entry from the bucket
	opcode del_entry(string id);
	//Tries to find entry in a bucket. On success returns pointer to entry, on failure returns 0
	stbl_entry* find_entry(string id);
	stbl(uint32_t);
	~stbl();
};