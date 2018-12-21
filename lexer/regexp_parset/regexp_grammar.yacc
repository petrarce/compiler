/*declarations*/
%start	S
%left '-'
%left '&'
%left '+'
%left '*'

%%
/*rules*/
S 	: Exp								{printf("S=>Exp;\n");};

Exp	: 		'(' Exp ')'					{printf("Exp=>(Exp);\n");}
		| 	Exp '*' Exp 				{printf("Exp=>Exp*Exp;\n");}
		|	Exp '+' Exp 				{printf("Exp=>Exp+Exp;\n");}
		|	Exp '&' Exp 				{printf("Exp=>Exp&Exp;\n");}
		|	Exp '-' Exp 				{printf("Exp=>Exp-Exp;\n");}
		| 	Exp '*'						{printf("Exp=>Exp*;\n");}
		| 	_Exp 						{printf("Exp=>_Exp;\n");};

_Exp:		_Exp Set 					{printf("_Exp=>_Exp Set;\n");}
		|	_Exp Symb					{printf("_Exp=>_Exp Symb;\n");}
		|	Symb						{printf("_Exp=>Symb;\n");}
		|	Set 						{printf("_Exp=>Set;\n");};				

Set	:		'{' Set_i '}'				{printf("Set=>{Set_i};\n");};

Set_i: 		Symb ',' Set_i				{printf("Set_i=>Symb , Set_i;\n");};
		| 	Symb						{printf("Set_i=>Symb;\n");};

Symb: 		'a'							{printf("Symb=>a\n");}
		| 	'b'							{printf("Symb=>b\n");}
		|	'0'							{printf("Symb=>eps\n");};


%%
/*programs*/