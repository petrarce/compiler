#define BOOST_TEST_MODULE REGEXP_PARSER
#include <boost/test/included/unit_test.hpp>
#include <types.hpp>
#include <nfa.hpp>
#include <lexer_regexps.hpp>
#include "regexp_parser.hpp"


BOOST_AUTO_TEST_CASE(REGEXP_check_parser)
{
	nfa test_nfa;
	string str_regexp = "/\\*(("ALL_SYMB"|/)|(\\*\\**"ALL_SYMB"))*\\*\\**/";

	regex2nfa(str_regexp, COMMENT, test_nfa);
	string inp_str = "/*hello this is\n\t comment/////******/";
	analyse_map_s* res = test_nfa.nfa_bt_next(inp_str);
	BOOST_REQUIRE_MESSAGE(res, "something wrong here");
	BOOST_CHECK_MESSAGE(res->analysed_str == "/*hello this is\n\t comment/////******/", 
							"something wrong here");
	delete res;

	str_regexp = "(a*bc\\*)|(c*ab)";
	regex2nfa(str_regexp, ID, test_nfa);

	test_nfa.nfa_reset();
	inp_str = "abc*";
	res = test_nfa.nfa_bt_next(inp_str);
	BOOST_CHECK_MESSAGE(res, "something wrong here");
	delete res;

	test_nfa.nfa_reset();
	inp_str = "bc*";
	res = test_nfa.nfa_bt_next(inp_str);
	BOOST_CHECK_MESSAGE(res, "something wrong here");
	delete res;


	test_nfa.nfa_reset();
	inp_str = "aaaaaaabc*";
	res = test_nfa.nfa_bt_next(inp_str);
	BOOST_CHECK_MESSAGE(res, "something wrong here");
	delete res;

	test_nfa.nfa_reset();
	inp_str = "aaaaaaac*";
	res = test_nfa.nfa_bt_next(inp_str);
	BOOST_CHECK_MESSAGE(!res, "something wrong here");
	delete res;

	test_nfa.nfa_reset();
	inp_str = "abc";
	res = test_nfa.nfa_bt_next(inp_str);
	BOOST_CHECK_MESSAGE(res, "something wrong here");
	delete res;

	test_nfa.nfa_reset();
	inp_str = "cab";
	res = test_nfa.nfa_bt_next(inp_str);
	BOOST_CHECK_MESSAGE(res, "something wrong here");
	delete res;

	test_nfa.nfa_reset();
	inp_str = "ab";
	res = test_nfa.nfa_bt_next(inp_str);
	BOOST_CHECK_MESSAGE(res, "something wrong here");
	delete res;

	test_nfa.nfa_reset();
	inp_str = "cb";
	res = test_nfa.nfa_bt_next(inp_str);
	BOOST_CHECK_MESSAGE(!res, "something wrong here");
	delete res;



}
