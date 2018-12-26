#pragma once

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
