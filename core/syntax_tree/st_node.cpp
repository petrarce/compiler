#include <iostream>
#include <stbl.hpp>
#include <types.hpp>
#include <st_node.hpp>

using namespace std;

node::node(int tag_val):
	tag(tag_val),
	prog_ok(false)
{}

void node::eval_child_attributes()
{
	for(shared_ptr<node> const child : this->child_list){
		child->eval_attributes();
	}
}

void node::add_child(shared_ptr<node> child)
{
	this->child_list.push_back(child);
}

void node::eval_attributes()
{
	this->eval_child_attributes();
	this->eval_local_attributes();
}

node::~node()
{
	child_list.clear();
}


void prog::eval_local_attributes(){
	switch(this->tag){
		case prog::PROG1: 
			this->prog_ok = child_list[0]->get_prog_ok();
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
prog::prog(PROD_PROG tag_val) : node(tag_val){}
prog::~prog(){}

void stmt::eval_local_attributes(){
	switch(this->tag){
		case stmt::STMT1: 
		case stmt::STMT2:
			this->prog_ok = child_list[0]->get_prog_ok() && child_list[1]->get_prog_ok();
			break;
		case stmt::STMT3:
			this->prog_ok = child_list[0]->get_prog_ok();
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
stmt::stmt(PROD_STMT tag_val) : node(tag_val){}
stmt::~stmt(){}

void _stmt::eval_local_attributes(){
	switch(this->tag){
		case _stmt::_STMT1:
		case _stmt::_STMT2:
		case _stmt::_STMT3:
		case _stmt::_STMT4:
			this->prog_ok = child_list[0]->get_prog_ok();
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
_stmt::_stmt(PROD_SUB_STMT tag_val) : node(tag_val){}
_stmt::~_stmt(){}

void def::eval_local_attributes(){
	switch(this->tag){
		case def::DEF1:
			this->prog_ok = child_list[1]->get_prog_ok();
		case def::DEF2:
			this->prog_ok = child_list[0]->get_prog_ok();
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
def::def(PROD_DEF tag_val) : node(tag_val){}
def::~def(){}

void _def::eval_local_attributes(){
	switch(this->tag){
		case _def::_DEF1:
			this->prog_ok = child_list[0]->get_prog_ok() && child_list[1]->get_prog_ok();
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
_def::_def(PROD_SUB_DEF tag_val) : node(tag_val){}
_def::~_def(){}

void varlist::eval_local_attributes(){
	switch(this->tag){
		case varlist::VARLIST1:
			this->prog_ok = child_list[1]->get_prog_ok();
			break;
		case varlist::VARLIST2:
			this->prog_ok = child_list[1]->get_prog_ok() && child_list[2]->get_prog_ok();
			break;
		case varlist::VARLIST3:
			this->prog_ok = true;
			break;
		case varlist::VARLIST4:
			this->prog_ok = child_list[1]->get_prog_ok();
			break;
		default:
			assert(0);
			break;
	}

	stbl& symb_table = *stbl::get_instance();
	opcode status = STATUS_OK;
	if(symb_table.find_entry(((type*)child_list[0].get())->get_type_val())){
		printf("SEMANTIC ERROR: %s was already declared\n", ((type*)child_list[0].get())->get_type_val().data());
		this->prog_ok = false;
	} else {
		status = symb_table.add_entry(((type*)child_list[0].get())->get_type_val(), "type - need to fix in future");
		assert(status == STATUS_OK);
	}

	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
varlist::varlist(PROD_VARLIST tag_val) : node(tag_val){}
varlist::~varlist(){}

void type::eval_local_attributes(){
	switch(this->tag){
		case type::TYPE1:
			this->prog_ok = true;
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
type::type(PROD_TYPE tag_val, string val) : 
	node(tag_val),
	type_val(val){}
type::~type(){}

void if_prod::eval_local_attributes(){
	switch(this->tag){
		case if_prod::IF1:
			this->prog_ok = child_list[0]->get_prog_ok() && child_list[1]->get_prog_ok() && child_list[2]->get_prog_ok();
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
if_prod::if_prod(PROD_IF_PROD tag_val) : node(tag_val){}
if_prod::~if_prod(){}

void while_prod::eval_local_attributes(){
	switch(this->tag){
		case while_prod::WHILE1:
			this->prog_ok = child_list[0]->get_prog_ok() && child_list[1]->get_prog_ok();
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
while_prod::while_prod(PROD_WHILE_PROD tag_val) : node(tag_val){}
while_prod::~while_prod(){}

void assign::eval_local_attributes(){
	stbl& symb_table = *stbl::get_instance();
	switch(this->tag){
		case assign::ASSIGN1:
			if(!symb_table.find_entry(((id*)child_list[0].get())->get_id_val())){
				printf("SEMANTIC ERROR: %s was not defined previously...\n", ((id*)child_list[0].get())->get_id_val().data());
				this->prog_ok = false;
				break;
			}
			this->prog_ok = child_list[1]->get_prog_ok();
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
assign::assign(PROD_ASSIGN tag_val) : node(tag_val){}
assign::~assign(){}

void procedure::eval_local_attributes(){
	switch(this->tag){
		case procedure::PROCEDURE1:
			this->prog_ok = child_list[1]->get_prog_ok();
			break;
		case procedure::PROCEDURE2:
			this->prog_ok = true;
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
procedure::procedure(PROD_PROCEDURE tag_val) : node(tag_val){}
procedure::~procedure(){}

void args::eval_local_attributes(){
	switch(this->tag){
		case args::ARGS1:
			this->prog_ok = child_list[0]->get_prog_ok();
			break;
		case args::ARGS2:
			this->prog_ok = child_list[0]->get_prog_ok() && child_list[0]->get_prog_ok();
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
args::args(PROD_ARGS tag_val) : node(tag_val){}
args::~args(){}

void arg::eval_local_attributes(){
	switch(this->tag){
		case arg::ARG1:
			this->prog_ok = child_list[0]->get_prog_ok();
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
arg::arg(PROD_ARG tag_val) : node(tag_val){}
arg::~arg(){}

void expr::eval_local_attributes(){
	switch(this->tag){
		case EXPR1:
		case EXPR11:
			this->prog_ok = child_list[0]->get_prog_ok();
			break;
		case EXPR2:
		case EXPR3:
		case EXPR4:
		case EXPR5:
		case EXPR6:
		case EXPR7:
		case EXPR8:
		case EXPR9:
		case EXPR10:
			this->prog_ok = child_list[0]->get_prog_ok() && child_list[1]->get_prog_ok();
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
expr::expr(PROD_EXPR tag_val) : node(tag_val){}
expr::~expr(){}

void obj::eval_local_attributes(){
	stbl& symb_table = *stbl::get_instance();
	switch(this->tag){
		case obj::OBJ1:
			if(!symb_table.find_entry(((id*)child_list[0].get())->get_id_val())){
				printf("SEMANTIC ERROR: %s was not defined previously...\n", ((id*)child_list[0].get())->get_id_val().data());
				this->prog_ok = false;
				break;
			}
		case obj::OBJ2:
		case obj::OBJ3:
			this->prog_ok = true;
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
obj::obj(PROD_OBJ tag_val) : node(tag_val){}
obj::~obj(){}

void id::eval_local_attributes(){
	switch(this->tag){
		case id::ID1:
			this->prog_ok = true;
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}

}
id::id(PROD_ID tag_val, string val) : 
	node(tag_val),
	id_val(val){}
id::~id(){}

void literal::eval_local_attributes(){
	switch(this->tag){
		case literal::LITERAL1:
			this->prog_ok = true;
			break;
		default:
			assert(0);
			break;
	}
	if(!this->prog_ok){
		pr_dbg("prog_ok=false");
	}
}
literal::literal(PROD_LITERAL tag_val) : node(tag_val){}
literal::~literal(){}