#define BOOST_TEST_MODULE REGEXP_PARSER
#include <boost/test/included/unit_test.hpp>
#include <types.hpp>
#include <nfa.hpp>
#include "regexp_parser.hpp"



BOOST_AUTO_TEST_CASE(REGEXP_check_parser)
{
	string str_regexp = "(a*bc\\*)|(c*ab)";
	nfa test_nfa;
	regex2nfa(str_regexp, ID, test_nfa);

	test_nfa.nfa_reset();
	string inp_str = "abc*";
	analyse_map_s* res = test_nfa.nfa_bt_next(inp_str);
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
