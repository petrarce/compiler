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
		|	'('Exp')''*' Exp 			{printf("Exp=>(Exp)*Exp;\n");}
		|	'('Exp')''*'				{printf("Exp=>(Exp)*;\n");}
		|	Exp '+' Exp 				{printf("Exp=>Exp+Exp;\n");}
		|	Exp '&' Exp 				{printf("Exp=>Exp&Exp;\n");}
		|	Exp '-' Exp 				{printf("Exp=>Exp-Exp;\n");}
		| 	_Exp

_Exp:		_Exp _Term					{printf("_Exp=>_Exp _Term;\n");}
		|	_Exp _Clause				{printf("_Exp=>_Exp _Clause;\n");}
		|	_Clause						{printf("_Exp=>_Clause;\n");}
		|	_Term						{printf("_Exp=>_Term;\n");};

_Clause:	_Term'*'					{printf("_Clause=>_Term*;\n");};

_Term:		Set 						{printf("_Term=>Set;\n");}
		| 	Symb						{printf("_Term=>Symb;\n");};;



Set	:		'{' Set_i '}'				{printf("Set=>{Set_i};\n");};

Set_i: 		Symb ',' Set_i				{printf("Set_i=>Symb , Set_i;\n");};
		| 	Symb						{printf("Set_i=>Symb;\n");};

Symb: 		'a'							{printf("Symb=>a\n");}
		| 	'b'							{printf("Symb=>b\n");}
		|	'0'							{printf("Symb=>eps\n");};


%%
/*programs*/