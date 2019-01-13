#include <string>
#include <vector>
#include <types.hpp>

using namespace std;

#define SYMB "q|w|e|r|t|y|u|i|o|p|a|s|d|f|g|h|j|" \
				"k|l|z|x|c|v|b|n|m|_|Q|W|E|R|T|Y|" \
				"U|I|O|P|A|S|D|F|G|H|J|K|L|Z|X|C|V|B|N|M"
#define NUMB "1|2|3|4|5|6|7|8|9|0"

static vector<string> regexp_vec = {
	//"("SYMB")""("NUMB"|"SYMB")*",	//regexp for ID
	"/\\*("SYMB"|"NUMB"| )*\\*/"
};
static vector<enum SATOKENS> regexp_analysis = {
	//ID,
	COMMENT
};