#include <string>
#include <vector>
#include <types.hpp>

using namespace std;

/*
	TAKE IN ACCOUNT NEXT SPECIAL SYMBOLS for regular expressions: '*', '|', '&', '-', '(', ')', '{', '}', ',' 
	they can be disabled by "\" ecraniser
*/

#define SYMB "q|w|e|r|t|y|u|i|o|p|a|s|d|f|g|h|j|" \
				"k|l|z|x|c|v|b|n|m|_|Q|W|E|R|T|Y|" \
				"U|I|O|P|A|S|D|F|G|H|J|K|L|Z|X|C|V|B|N|M"
#define NUMB "1|2|3|4|5|6|7|8|9|0"
#define SPEC "\\(|\\)|\\{|\\}|;|:"
#define OPER "\\-\\-|++|\\-|+|\\*|/|==|=|\\|\\||\\&\\&|\\||\\&|>|<|%"
#define DELIM " |\t|\n|\r"

static vector<string> regexp_vec = {
	"/\\*("SYMB"|"NUMB"|"SPEC"|"OPER"|"DELIM")*\\*/",
	"//("SYMB"|"NUMB"|"SPEC"|"OPER"| |\t)*",
	DELIM,
	"int",
	"real",
	"double",
	"if",
	"while",
	"for",
	SPEC,
	OPER,
	"\"("DELIM"|"NUMB"|"SPEC"|"OPER"|"SYMB")*\"",
	"("NUMB")*",
	"("SYMB")""("NUMB"|"SYMB")*",	//regexp for ID
};
static vector<enum SATOKENS> regexp_analysis = {
	COMMENT,
	COMMENT,
	DELIMITER,
	TYPE,
	TYPE,
	TYPE,
	KEYWORD,
	KEYWORD,
	KEYWORD,
	SPECIAL,
	OPERATOR,
	LITERAL,
	LITERAL,
	ID
};