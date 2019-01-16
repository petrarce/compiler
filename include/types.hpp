#pragma once
#include <vector>
#include <cstdint>
#include <string>

using namespace std;

enum SATOKENS
{
	COMMENT = 0,
	ID,
	DELIMITER,
	TYPE,
	KEYWORD,
	SPECIAL,
	OPERATOR,
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
	KEYWORD,
	SPECIAL,
	OPERATOR,
	LITERAL,
	REGEXP
};
static vector<string> la_str = {	
	"COMMENT",
	"ID",
	"DELIMITER",
	"TYPE",
	"KEYWORD",
	"SPECIAL",
	"OPERATOR",
	"LITERAL",
	"REGEXP"
};

#define pr_dbg(msg, args...) printf("[%s:%d] " msg "\n", ##args)

#define assert(exp) { \
	if(exp) { \
		printf("[%s,%d]assertion failes: %s", __FUNCTION__, __LINE__, #exp); \
		exit(-1); \
	} \
}
