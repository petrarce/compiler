#pragma once
#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <boost/stacktrace.hpp>

using namespace std;

#ifdef DEBUG
#define assert(exp) { \
	if(!(exp)) { \
		pr_dbg("assertion failes: %s", #exp); \
		cout << boost::stacktrace::stacktrace(); \
		exit(-1); \
	} \
}

#define pr_dbg(msg, args...) printf("[%s:%d] " msg "\n", __FILE__, __LINE__, ##args)
#else
#define pr_dbg(msg, args...) 
#define assert(expr) 
#endif


enum SATOKENS
{
	COMMENT = 0,
	ID,
	DELIMITER,
	TYPE,
	IF,
	WHILE,
	ELSE,
	SPECIAL,
	OPERATOR,
	OPEREQ,
	OPERNEQ,
	OPERINC,
	OPERDEC,
	OPERAND,
	OPEROR,
	LITERAL,
	REGEXP
};

enum opcode
{
	STATUS_OK,
	STATUS_NOK,
	STATUS_ALREADY_EXISTS,
	STATUS_INVALID_ARG,
	STATUS_NO_ENTRY,
	STATUS_ALLOC_FAILED,
	STATUS_STRING_IS_EMPTY
};

static vector<uint8_t> sa_tokens = {
	COMMENT,
	ID,
	DELIMITER,
	TYPE,
	IF,
	WHILE,
	ELSE,
	SPECIAL,
	OPERATOR,
	OPEREQ,
	OPERNEQ,
	OPERINC,
	OPERDEC,
	OPERAND,
	OPEROR,
	LITERAL,
	REGEXP
};
static vector<string> la_str = {	
	"COMMENT",
	"ID",
	"DELIMITER",
	"TYPE",
	"IF",
	"WHILE",
	"ELSE",
	"SPECIAL",
	"OPERATOR",
	"OPEREQ",
	"OPERNEQ",
	"OPERINC",
	"OPERDEC",
	"OPERAND",
	"OPEROR",
	"LITERAL",
	"REGEXP"
};

