#include <iostream>
#include <vector>
#include <string>
#include <types.hpp>
#include <stbl.hpp>

using namespace std;

opcode stbl_entry::set_last(stbl_entry* entry)
{
	assert(!entry);
	assert(this == entry);
	stbl_entry* cur = this;
	while(cur->next){
		cur = cur->next;
	}
	cur->next = entry;
	return STATUS_OK;
}

uint32_t stbl::calc_hash(string id)
{

	hash<string> hash_fn;
	return hash_fn(id) % this->buckets.size();
}

opcode stbl::add_entry(string id, string type)
{
	assert(find_entry(id));

	uint32_t bucket_num = calc_hash(id);
	stbl_entry* new_entry = new stbl_entry(id, type);
	if(!this->buckets[bucket_num]){
		this->buckets[bucket_num] = new_entry;
	} else {
		this->buckets[bucket_num]->set_last(new_entry);
	}

	return STATUS_OK;
}

opcode stbl::del_entry(string id)
{
	uint32_t bucket_num = calc_hash(id);
	stbl_entry* cur_entry = NULL;
	if(!this->buckets[bucket_num]){
		return STATUS_OK;
	}

	//delete element in the head of bucket
	if(this->buckets[bucket_num]->id == id){
		stbl_entry* next = this->buckets[bucket_num]->next;
		delete this->buckets[bucket_num];
		this->buckets[bucket_num] = next;
		return STATUS_OK;
	}

	//delete element that is not in the head of bucket
	cur_entry = this->buckets[bucket_num];
	while(cur_entry->next){
		if(cur_entry->next->id == id){
			stbl_entry* next = cur_entry->next->next;
			delete cur_entry->next;
			cur_entry->next = next;
			break;
		}
	}

	return STATUS_OK;
}

stbl_entry* stbl::find_entry(string id)
{

	uint32_t bucket_num = calc_hash(id);
	stbl_entry* cur_entry = this->buckets[bucket_num];

	while(cur_entry){
		if(cur_entry->id == id){
			return cur_entry;
		}
		cur_entry = cur_entry->next;
	}
	return NULL;
}

opcode stbl::clean_buckets()
{
	for(int i = 0; i < this->buckets.size(); i++){
		stbl_entry* next;
		stbl_entry* cur = this->buckets[i];
		while(cur){
			next = cur->next;
			delete cur;
			cur = next;
		}
		this->buckets[i] = NULL;
	}
	return STATUS_OK;
}

opcode stbl::print()
{
	printf("___________________________________\n");
	printf("|\tID\t|\tTYPE\t|\n");
	printf("___________________________________\n");
	for(stbl_entry* entry : this->buckets){
		while(entry){
			printf("|\t%s\t|\t%s\t|\n", entry->id.begin(), entry->type.begin());
			entry = entry->next;
		}
	}
	printf("___________________________________\n");

	return STATUS_OK;
}

stbl::stbl(uint32_t size)
{
	this->buckets.resize(size);
}

stbl::~stbl()
{
	clean_buckets();
	buckets.clear();
}