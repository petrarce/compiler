#include <iostream>
#include <string>
#include <vector>
#include <types.hpp>

using namespace std;

class node{
protected:
	int tag;
	vector<node*> child_list;
	/*attributes section*/
	bool prog_ok;

	virtual void eval_local_attributes()=0;
	void eval_child_attributes();
public:
	void add_child(node* chld);
	void eval_attributes();
	bool get_prog_ok(){return prog_ok;};
	node(int);
	virtual ~node();
private:
	node(){};
	node(node& obj){};
	node& operator=(const node& obj){return *this;};

};

/*PROG*/
class prog : public node{
private:
	virtual void eval_local_attributes();
public:
	enum PROD_PROG{
		PROG1 = 0	//PROG->STMT
	};
	prog(PROD_PROG);
	virtual ~prog();
};

class stmt : public node{
private:
	virtual void eval_local_attributes();
public:
	enum PROD_STMT{
		STMT1,	//STMT-> DEF STMT
		STMT2,	//STMT-> _STMT STMT
		STMT3	//STMT-> _STMT
	};
public:
	stmt(PROD_STMT);
	virtual ~stmt();
};

class _stmt : public node{
private:
	virtual void eval_local_attributes();
public:
	enum PROD_SUB_STMT{
		_STMT1,	//_STMT-> IF
		_STMT2,	//_STMT-> WHILE
		_STMT3,	//_STMT-> ASSIGN
		_STMT4	//_STMT-> PROCEDURE
	};
public:
	_stmt(PROD_SUB_STMT);
	virtual ~_stmt();
};

class def : public node{
private:
	virtual void eval_local_attributes();
public:
	enum PROD_DEF{
		DEF1,	//  DEF _DEF
		DEF2	// _DEF
	};
public:
	def(PROD_DEF);
	virtual ~def();
};

class _def : public node{
private:
	virtual void eval_local_attributes();
public:
	enum PROD_SUB_DEF{
		_DEF1,	//TYPE VARLIST
	};
public:
	_def(PROD_SUB_DEF);
	virtual ~_def();
};

class varlist : public node{
private:
	virtual void eval_local_attributes();
public:
	enum PROD_VARLIST{
		VARLIST1,	//ID, VARLIST
		VARLIST2,	//ID = EXPR, VARLIST
		VARLIST3,	//ID
		VARLIST4	//ID = EXPR
	};
public:
	varlist(PROD_VARLIST);
	virtual ~varlist();
};

class type : public node{
private:
	string type_val;
	virtual void eval_local_attributes();
public:
	enum PROD_TYPE{
		TYPE1	//Type
	};
public:
	opcode set_type_val(string str){this->type_val = str; return STATUS_OK;};
	string get_type_val(){return this->type_val;};
	type(PROD_TYPE, string);
	virtual ~type();
};

class if_prod : public node{
private:
	virtual void eval_local_attributes();
public:
	enum PROD_IF_PROD{
		IF1	//If(EXPR){STMT}Else{STMT}
	};
public:
	if_prod(PROD_IF_PROD);
	virtual ~if_prod();
};

class while_prod : public node{
private:
	virtual void eval_local_attributes();
public:
	enum PROD_WHILE_PROD{
		WHILE1	//While'('EXPR')''{'STMT'}'
	};
public:
	while_prod(PROD_WHILE_PROD);
	virtual ~while_prod();
};

class assign : public node{
private:
	virtual void eval_local_attributes();
public:
	enum PROD_ASSIGN{
		ASSIGN1	//ID = EXPR
	};
public:
	assign(PROD_ASSIGN);
	virtual ~assign();
};

class procedure : public node{
private:
	virtual void eval_local_attributes();
public:
	enum PROD_PROCEDURE{
		PROCEDURE1,	//ID(ARGS)
		PROCEDURE2	//ID()
	};
public:
	procedure(PROD_PROCEDURE);
	virtual ~procedure();
};

class args : public node{
private:
	virtual void eval_local_attributes();
public:
	enum PROD_ARGS{
		ARGS1,	//ARG
		ARGS2	//ARG, ARGS
	};
public:
	args(PROD_ARGS);
	virtual ~args();
};

class arg : public node{
private:
	virtual void eval_local_attributes();
public:
	enum PROD_ARG{
		ARG1,	//EXPR
	};
public:
	arg(PROD_ARG);
	virtual ~arg();
};

class expr : public node{
private:
	virtual void eval_local_attributes();
public:
	enum PROD_EXPR{
		EXPR1,	//OBJ
		EXPR2,	//EXPR '+' EXPR
		EXPR3,	//EXPR '-' EXPR
		EXPR4,	//EXPR '*' EXPR
		EXPR5,	//EXPR '/' EXPR
		EXPR6,	//EXPR '%' EXPR
		EXPR7,	//EXPR '<' EXPR
		EXPR8,	//EXPR '>' EXPR
		EXPR9,	//EXPR Eq EXPR
		EXPR10,	//EXPR Neq EXPR
		EXPR11,	//('EXPR')
	};
public:
	expr(PROD_EXPR);
	virtual ~expr();
};

class obj : public node{
private:
	virtual void eval_local_attributes();
public:
	enum PROD_OBJ{
		OBJ1,	//ID
		OBJ2,	//LITERAL
		OBJ3	//PROCEDURE
	};
public:
	obj(PROD_OBJ);
	virtual ~obj();
};

class id : public node{
private:
	string id_val;
	virtual void eval_local_attributes();
public:
	enum PROD_ID{
		ID1,	//Id
	};
public:
	opcode set_id_val(string str){this->id_val = str; return STATUS_OK;};
	string get_id_val(){return this->id_val;};
	id(PROD_ID, string);
	virtual ~id();
};

class literal : public node{
private:
	virtual void eval_local_attributes();
public:
	enum PROD_LITERAL{
		LITERAL1	//Literal
	};
public:
	literal(PROD_LITERAL);
	virtual ~literal();
};