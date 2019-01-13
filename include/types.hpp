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

#define assert(exp) { \
	if(exp) { \
		printf("[%s,%d]assertion failes: %s", __FUNCTION__, __LINE__, #exp); \
		exit(-1); \
	} \
}