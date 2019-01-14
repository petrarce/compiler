/*declarations*/
%token Int Real Id If Else While Literal
%%
/*rules*/
Prog: 				DEF STMT

DEF: 				TYPE VARLIST";"
				|	DEF DEF

TYPE: 				Int 
				| 	Real

VARLIST: 			VARDEFINITION 
				| 	VARDEFINITION"," VARLIST 

VARDEFINITION: 		Id 
				| 	Id "=" EXPR


STMT: 	
					DEF STMT
				| 	STMT STMT
				| 	IF
				| 	WHILE
				| 	ASSIGN
				| 	PROCEDURE

IF:					If"("EXPR")""{"STMT"}"Else"{"STMT"}"
WHILE:				While"("EXPR")""{"STMT"}"
ASSIGN:				Id "=" EXPR";"

PROCEDURE: 			Id"("ARGS)";"

ARGS:				ARG 
				| 	ARG"," ARGS

ARG:				VARDEFINITION 
				| 	EXPR 

EXPR: 				OBJ
				| 	EXPR "+" EXPR
				| 	EXPR "-" EXPR
				| 	EXPR "*" EXPR
				| 	EXPR "/" EXPR
				| 	EXPR "%" EXPR
				| 	"("EXPR")"

OBJ:				Id 
				| 	Literal

%%
/*programs*/