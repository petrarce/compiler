#include <nfa.hpp>
#include <string>
#include <cstring>
#include <algorithm>
#include <types.hpp>
#include <memory>
#include <queue>
#include <map>
class inv_arg_ex inv_arg_ex_obj;
class empty_str_ex empty_str_ex_obj;

static void my_set_union(vector<uint32_t>& dest, vector<uint32_t>& src)
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

static opcode append_aplphabet(vector<char>& dst_alphabet, vector<char>& src_alphabet)
{
	assert(dst_alphabet.size() == src_alphabet.size());

	for(int i = 0; i < dst_alphabet.size(); i++){
		if(dst_alphabet[i] || !src_alphabet[i]){
			continue;
		}
		dst_alphabet[i] = src_alphabet[i];
	}
	return STATUS_OK;
}

void push_states_with_offset(nfa& temp_nfa, nfa& nfa_x)
{
	uint32_t offset = temp_nfa.states.size();
	for(state_c st : nfa_x.states){
		//add offset to state id
		st.id += offset;
		//add offset to state_ids in transition table
		for(size_t i = 0; i < st.transition_table.size(); i++){
			for(size_t j = 0; j < st.transition_table[i].state_ids.size(); j++){
				st.transition_table[i].state_ids[j] += offset;
			}
		}
		//put state into temp_nfa
		temp_nfa.states.push_back(st);
	}

	append_aplphabet(temp_nfa.alphabet, nfa_x.alphabet);
}



nfa 	nfa::nfa_convert_clausure(nfa& nfa_a)
{
	nfa temp_nfa = nfa_a;

	// add two new states: intermediate and new_final
	state_c intermadiate, new_final;
	intermadiate.id = temp_nfa.states.size();
	new_final.id 	= intermadiate.id + 1;
	temp_nfa.states.push_back(intermadiate);
	temp_nfa.states.push_back(new_final);

	// get list of all accepting states
	vector<uint32_t> acc_st_list;
	for(uint32_t i = 0; i < temp_nfa.states.size(); i++){
		if(temp_nfa.states[i].is_accepting){
			acc_st_list.push_back(temp_nfa.states[i].id);
		}
	}

	// link creates states
	for(uint32_t st_id : acc_st_list){
		temp_nfa.link_state(st_id, EPS, intermadiate.id);
	}
	temp_nfa.link_state(0, EPS, new_final.id);
	temp_nfa.link_state(intermadiate.id, EPS, new_final.id);
	temp_nfa.link_state(intermadiate.id, EPS, 0);

	
	// reset all accepting states
	for(uint32_t st_id : acc_st_list){
		temp_nfa.states[st_id].is_accepting = false;
	}
	temp_nfa.states[new_final.id].is_accepting = true;

	return temp_nfa;
}

nfa 	nfa::nfa_convert_concat(nfa& nfa_a, nfa& nfa_b)
{
	nfa temp_nfa = nfa_a;

	//create intermediate state
	state_c intermediate;
	intermediate.id = nfa_a.states.size();	
	//add intermediate to nfa_a
	temp_nfa.states.push_back(intermediate);
	//get list of all accepting states in nfa_a
	//link all accepting of nfa_a to intermediate
	//reset all accepting states of nfa_a
	for(state_c st : temp_nfa.states){
		if(st.is_accepting){
			temp_nfa.link_state(st.id, EPS, intermediate.id);
			temp_nfa.states[st.id].is_accepting = false;
		}
	}
	//for all states in nfa_b do:
	uint32_t offset = temp_nfa.states.size();
	for(state_c st : nfa_b.states){
		//increase id of state		
		st.id += offset;
		//increase state_ids in transition table
		for(size_t i = 0; i < st.transition_table.size(); i++){
			if(st.transition_table[i].symb == 0)
				continue;
			for(size_t j = 0; j <  st.transition_table[i].state_ids.size(); j++){
				st.transition_table[i].state_ids[j] += offset;
			}
		}
		//add state to nfa_a
		temp_nfa.states.push_back(st);
	}
	//link intermediate state with first state of nfa_b
	temp_nfa.link_state(intermediate.id, EPS, offset);
	//return nfa_a
	append_aplphabet(temp_nfa.alphabet, nfa_b.alphabet);
	return temp_nfa;
	//append alphabet from nfa_b to nfa_a

}


nfa 	nfa::nfa_convert_union(nfa& nfa_a, nfa& nfa_b)
{
	nfa temp_nfa;
	push_states_with_offset(temp_nfa, nfa_a);
	temp_nfa.link_state(0, EPS, 1);

	push_states_with_offset(temp_nfa, nfa_b);
	temp_nfa.link_state(0, EPS, nfa_a.states.size()+1);

	return temp_nfa;
}

opcode nfa::init_cur_state_list()
{
	this->cur_state_list.clear();
	cur_state_list.push_back(0);
	return STATUS_OK;
}

opcode nfa::deinit_cur_state_list()
{
	this->cur_state_list.clear();
	return STATUS_OK;
}


vector<uint32_t> nfa::transition_get_next_states(uint32_t state, uint8_t symb)
{

	return this->states[state].transition_table[symb].state_ids;
}

opcode nfa::link_state(uint32_t state1, char symb, uint32_t state2)
{
	opcode status;
	uint32_t state_highest = (state1>state2)?state1:state2;
	if(this->states.size() < (state_highest + 1)){ //state ids are started from 0
		uint32_t max_state_id = this->states.back().id;
		this->states.resize(state_highest + 1);
		for(size_t i = max_state_id + 1; i < this->states.size(); i++){
			this->states[i].id = i;
		}
	}
	this->alphabet[symb] = symb;
	status = states[state1].transition_table_add_entry(symb, state2);
	return status;
}

opcode nfa::link_state(uint32_t state1, const string& symbs, uint32_t state2)
{
	//if string is empty link failed states with eps transition
	if(!symbs.size()){
		link_state(state1, EPS, state2);
	}

	for(char c : symbs){
		link_state(state1, c, state2);
	}

	return STATUS_OK;
}

//simple input parser overload
//regex for parser: [0-9][0-9]*@X*@[0-9][0-9]* 
opcode nfa::link_state(const string& str)
{
	uint8_t state = 0;
	string st1, st2, symbs;

	for (char c : str){
		if( '0' <= c && c <= '9' && state == 0 ){
			state = 1;
			st1.push_back(c);
		}else if('0'<= c && c <= '9' && state == 1){
			st1.push_back(c);
		}else if (c == '@' && state == 1){
			state = 2;
		}else if (c != '@' && state == 2)
			symbs.push_back(c);
		else if (c == '@' && state == 2)
			state = 3;
		else if ('0' <= c && c <= '9' && state == 3){
			state = 4;
			st2.push_back(c);
		}else if ('0' <= c && c <= '9' && state == 4)
			st2.push_back(c);
		else if (c == '\\' && state == 4){
			state = 0;
			link_state(stoi(st1), symbs, stoi(st2));
			st1.clear();
			st2.clear();
			symbs.clear();
		} else
		{
			cout << "[FATAL_ERROR] failed to parse links... you better start debugging" << symbs << endl;
			exit(STATUS_NOK);
		}

	}
	if(state != 0){
		cout << "incorrect parsing string, please recheck" << endl ;
		exit(STATUS_NOK);
	}
	return STATUS_OK;
}

string nfa::get_links()
{
	string res;

	for(const state_c& st1 : this->states ){
		for(const trans_table_t& tbl : st1.transition_table){
			for(uint32_t st2 : tbl.state_ids){
				string st1_str, st2_str, symb = "@";
				st1_str += to_string(st1.id);
				st2_str += to_string(st2);
				symb[0] = tbl.symb;
				if(symb[0]!=EPS){
					res += st1_str + "@" + symb + "@" + st2_str + "\\";
				} else {
					res += st1_str + "@" + "@" + st2_str + "\\";
				}
			}
		}
	}
	
	return res;
}



uint32_t nfa::nfa_status()
{

	for(uint32_t state : this->cur_state_list){
		if (this->states[state].is_accepting)
			return state;
	}
	return -1;

}

opcode nfa::nfa_clause(vector<uint32_t>& state_list)
{
	vector<uint32_t> tmp_state_list;
	vector<uint32_t> tmp_states_eps;
	tmp_state_list = state_list;
	do{
		state_list = tmp_state_list;
		for(uint32_t st : state_list){
			tmp_states_eps = transition_get_next_states(st, EPS);
			my_set_union(tmp_state_list, tmp_states_eps);
		}
	}while(state_list != tmp_state_list);
	return STATUS_OK;
}


opcode nfa::nfa_clause()
{
	return nfa_clause(this->cur_state_list);
}

opcode nfa::nfa_bt_log_save(uint32_t state,uint32_t position)
{
	vector<uint32_t> entry;
	entry.push_back(state);
	entry.push_back(position);
	this->bt_log.push_back(entry);
	return STATUS_OK;
}

analyse_map_s* nfa::nfa_bt_next(string& token)
{
	int state;
	analyse_map_s* analyse_map = new analyse_map_s();

	nfa_reset();
	nfa_clause();
	for (size_t i = 0; i < token.size(); i++){
		nfa_next(token[i]);
		sort(this->cur_state_list.begin(), this->cur_state_list.end());
		state = nfa_status();
		if(state != -1){
			nfa_bt_log_save(state, i);
		} else if(!this->cur_state_list.size()){ //check if our autometon is still allive if still allive - continue
			break;
		}
	}

	if(!this->bt_log.size()){			//if dead - check if in backlog there was at list one accepting state

		//if previously no accepted states was entered - lexical analysis failed
		delete analyse_map;
		return NULL;
	}
	//if was - we pring latest accepted analysis, and remove regarding string from nput
	analyse_map->analysed_str = token.substr(0, bt_log.back()[1]+1);
	analyse_map->analyse = this->states[bt_log.back()[0]].analyse;
	token.erase(0, bt_log.back()[1]+1);
	bt_log.clear();
	return analyse_map;

}
opcode nfa::nfa_bt_run(string& token, vector<string>& strs, vector<uint32_t> ignore)
{
	analyse_map_s* analyse_map;
	while(token.size()){
		analyse_map = nfa_bt_next(token);
		if(!analyse_map)
			return STATUS_NOK;
		assert(analyse_map->analyse <= strs.size());
		if(find(ignore.begin(), ignore.end(), analyse_map->analyse) == ignore.end()){
			printf("(\"%s\", %s)\n", analyse_map->analysed_str.begin(), strs[analyse_map->analyse].begin());
		}
		delete analyse_map;
	}
	return STATUS_OK;
}


opcode nfa::nfa_reset()
{
	init_cur_state_list();
	bt_log.clear();
	return STATUS_OK;
}

static string str_from_vect(vector<uint32_t>& vec)
{
	string	str;
	for(uint32_t val : vec){
		str.append(to_string(val));
	}
	return str;
}

opcode nfa::nfa_optimise()
{
	queue<vector<uint32_t>> 	todoList;
	map<string, uint32_t>		doneList;
	vector<uint32_t> 			st_cur;
	vector<uint32_t> 			st_next;
	uint32_t 					st_count = 0;
	nfa 						optimised_nfa;

	nfa_clause();
	st_cur = this->cur_state_list;
	todoList.push(st_cur);
	doneList.insert(pair<string, int>(str_from_vect(st_cur), st_count));
	st_count++;

	while(!todoList.empty()){
		st_cur = todoList.front();
		assert(doneList.find(str_from_vect(st_cur)) != doneList.end());
		uint32_t st1 = doneList.find(str_from_vect(st_cur))->second;
		uint32_t st2;
		todoList.pop();
		for(char symb : this->alphabet){
			if(!symb || symb == EPS){
				continue;
			}

			this->cur_state_list = st_cur;
			nfa_next(symb);
			if(!this->cur_state_list.size()){
				continue;
			}
			
			auto find_iter = doneList.find(str_from_vect(this->cur_state_list));
			if(find_iter == doneList.end()){
				todoList.push(this->cur_state_list);
				doneList.insert(pair<string, int>(str_from_vect(this->cur_state_list), st_count));
				st2 = st_count;
				st_count++;
			} else {
				st2 = find_iter->second;
			}
			optimised_nfa.link_state(st1, symb, st2);
			
			for(uint32_t st : this->cur_state_list){
				if(this->states[st].is_accepting){
					optimised_nfa.set_accepting(st2, this->states[st].analyse);
					break;
				}
			}
		}
	}
 	*this = optimised_nfa;
	return STATUS_OK;
}

void nfa::nfa_next(char symb)
{
	vector<uint32_t> new_cur_state_list;
	
	for (uint32_t state : this->cur_state_list){
		vector<uint32_t> tmp_states = transition_get_next_states(state, symb);

		my_set_union(new_cur_state_list, tmp_states);
	}
	this->cur_state_list = new_cur_state_list;
	nfa_clause();

}

opcode nfa::set_accepting(vector<uint32_t> states, enum SATOKENS analyse)
{
	for(uint32_t st : states){
		this->states[st].is_accepting 	= true;
		this->states[st].analyse		= analyse;
	}
	return STATUS_OK;
}

opcode nfa::set_accepting(uint32_t state, enum SATOKENS analyse)
{
	this->states[state].is_accepting = true;
	this->states[state].analyse		 = analyse;
	return STATUS_OK;
}

vector<pair<uint32_t, SATOKENS>> nfa::get_accepting(){
	vector<pair<uint32_t, SATOKENS>> accepting;
	for(const state_c& st : this->states){
		if(st.is_accepting){
			pair<uint32_t, SATOKENS> new_pair;
			new_pair.first 	= st.id;
			new_pair.second = st.analyse;
			accepting.push_back(new_pair);
		}
	}

	return accepting;
}

opcode nfa::set_analyse(enum SATOKENS token){

	for(size_t i = 0; i < this->states.size(); i++)		{
		this->states[i].analyse = token;
	}
	return STATUS_OK;
}

nfa::nfa()
{	
	this->states.resize(1);
	this->states[0].id = 0;
	this->alphabet.resize(256);
	for(char& c :  this->alphabet){
		c = 0;
	}
	init_cur_state_list();
}

nfa::~nfa(){

	this->states.clear();
	deinit_cur_state_list();
}
