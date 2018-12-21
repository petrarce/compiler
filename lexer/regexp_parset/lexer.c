#include "lexer.h"
#include <stdio.h>
#include <assert.h>

int yylex()
{
	lex_str.cur_pos++;
	return lex_str.inp_buf[lex_str.cur_pos - 1];	
}

int yyerror()
{
	printf("yyerror: some error occured!!!\n");
	return 0;
}
/*
char* strcat_my(char* str1, char* str2)
{
	assert(str1 != NULL);
	assert(str2 != NULL);

	char* new_str = malloc(strlen(str1) + strlen(str2) + 1);

	memcpy(new_str, strlen(str1), str1);
	memcpy(new_str, strlen(str2), str2);

	return new_str;

}
char* str_push_back(char* str1, char c)
{
	char* new_str;
	if(str1 == NULL){
		new_str = malloc(2);
		new_str[0] = c;
		return new_str
	}

	new_str = malloc(strlen(str1) + 2);
	memcpy(new_str, strlen(str1), str1);
	new_str[strlen(str1)] = c;

	return new_str;
}*/