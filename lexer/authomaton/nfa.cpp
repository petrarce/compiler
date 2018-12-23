#include <nfa.hpp>
#include <string>
#include <cstring>
#include <algorithm>

#ifdef DEBUG
#include <assert>
#else
#define assert(exp) 
#endif

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


opcode 	nfa::nfa_convert_clause(nfa& nfa_a)
{
	nfa temp_nfa = nfa_a;

	// add two new states: intermediate and new_final
	state_c* intermadiate = new state_c();
	// get list of all accepting states
	// link all accepting with intermediate with eps transitions
	// link first state with intermediate with eps transition
	// link intermediate state and new_finale with eps transition
	// reset all accepting states
	// set new_final as accepting

	return STATUS_OK;
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

	vector<uint32_t> 	states = this->states[state].transition_table[symb]->state_ids;
	//auto 		state_count = this->states[state].transition_table[symb]->state_count;

	//in transition table can be empty at this point (means, that any further transition leads to dead state)
	if(!this->states[state].transition_table[symb])
		return states_id;

	for(uint32_t  i = 0; i < this->states.size(); i++){
		for(uint32_t j : states){
			if(j == this->states[i].id){
				states_id.push_back(i);
			}
		}
	}

	return states_id;
}

opcode nfa::link_state(uint32_t state1, char symb, uint32_t state2)
{
	opcode status;
	status = states[state1].transition_table_add_entry(symb, state2);
	return status;
}

opcode nfa::link_state(uint32_t state1, string& symbs, uint32_t state2)
{
	opcode status;
	//if string is empty link failed states with eps transition
	if(!symbs.size())
		link_state(state1, EPS, state2);

	for(char c : symbs)
		link_state(state1, c, state2);

	return status;
}

//simple input parser overload
//regex for parser: [0-9][0-9]*@X*@[0-9][0-9]* 
opcode nfa::link_state(string& str)
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
			cout << "failed to parse string" << symbs << endl;
			exit(STATUS_NOK);
		}

	}
	if(state != 0){
		cout << "incorrect parsing string, please recheck" << endl ;
		exit(STATUS_NOK);
	}
	return STATUS_OK;
}


opcode nfa::nfa_run(string& str)
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
	return STATUS_OK;
}

uint32_t nfa::nfa_status()
{
	for(uint32_t state : this->cur_state_list){
		if (this->states[state].is_accepting)
			return state;
	}
	return 0;

}

opcode nfa::nfa_clause()
{
	vector<uint32_t> tmp_state_list;
	vector<uint32_t> tmp_states_eps;
	tmp_state_list = this->cur_state_list;
	do{
		this->cur_state_list = tmp_state_list;
		for(uint32_t st : this->cur_state_list){
			tmp_states_eps = transition_get_next_states(st, EPS);
			my_set_union(tmp_state_list, tmp_states_eps);
		}
	}while(this->cur_state_list != tmp_state_list);
	return STATUS_OK;
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
	uint32_t state;
	analyse_map_s* analyse_map = new analyse_map_s();

	nfa_reset();
	for (int i = 0; i < token.size(); i++){
		nfa_next(token[i]);
		sort(this->cur_state_list.begin(), this->cur_state_list.end());
		state = nfa_status();
		if(state){
			nfa_bt_log_save(state, i);
		} else if(!this->cur_state_list.size()){ //check if our autometon is still allive if still allive - continue
			break;
		}
	}

	if(!this->bt_log.size()){			//if dead - check if in backlog there was etlist one accepting state

		cout << "string is incorrect" << endl;	//if previously no accepted states was entered - lexical analysis failed
		delete analyse_map;
		return NULL;
	}
	//if was - we pring latest accepted analysis, and remove regarding string from nput
	analyse_map->str = token.substr(0, bt_log.back()[1]+1);
	analyse_map->analyse = this->states[bt_log.back()[0]].analyse;
	token.erase(0, bt_log.back()[1]+1);
	bt_log.clear();
	return analyse_map;

}
opcode nfa::nfa_bt_run(string& token, vector<string>& strs, vector<uint32_t> ignore)
{
	opcode state;
	analyse_map_s* analyse_map;
	while(token.size()){
		analyse_map = nfa_bt_next(token);
		if(!analyse_map)
			return STATUS_NOK;
		assert(analyse_map->analyse <= strs.size());
		if(find(ignore.begin(), ignore.end(), analyse_map->analyse) == ignore.end()) //2 = delimiter - remove this from here
			cout << "(\"" <<  analyse_map->str << "\", " << strs[analyse_map->analyse] << ") " <<  endl;
		
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

void nfa::nfa_next(char symb)
{
	vector<uint32_t> new_cur_state_list;
	
	nfa_clause();
	for (uint32_t state : this->cur_state_list){
		vector<uint32_t> tmp_states = transition_get_next_states(state, symb);

		my_set_union(new_cur_state_list, tmp_states);
	}
	this->cur_state_list = new_cur_state_list;
}

opcode nfa::set_accepting(vector<uint32_t> states, uint32_t analyse)
{
	for(uint32_t st : states){
		this->states[st].is_accepting 	= true;
		this->states[st].analyse		= analyse;
	}
}

opcode nfa::set_accepting(uint32_t state, uint32_t analyse)
{
	this->states[state].is_accepting = true;
	this->states[state].analyse		 = analyse;
	return STATUS_OK;
}

nfa::nfa(uint32_t states_count, char* alphabet)
{
	memset(this->alphabet, 0, sizeof(this->alphabet));
	for(int i = 0; i < strlen(alphabet); i++)
		this->alphabet[alphabet[i]] = alphabet[i];
	
	//initialise states
	this->states.resize(states_count);
		for(int i = 0; i < this->states.size(); i++){//enumerate state ids
		this->states[i].id = i;
	}

	init_cur_state_list();
}

nfa::~nfa(){

	this->states.clear();
	memset(this->alphabet, 0, sizeof(this->alphabet));
	deinit_cur_state_list();
}
