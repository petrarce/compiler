#define BOOST_TEST_MODULE WHILE_LEXER
#include <boost/test/included/unit_test.hpp>
#include <lexer.hpp>

BOOST_AUTO_TEST_CASE(LEXER_test_tokenisation)
{
	lexer test_lexer("int while /*comment*/ id");

	uint32_t token = test_lexer.get_next_token();
	BOOST_CHECK_MESSAGE(token == Type, "something wrong here");
	BOOST_CHECK_MESSAGE(test_lexer.get_cur_token_val() == "int", "something wrong here");

	token = test_lexer.get_next_token();
	BOOST_CHECK_MESSAGE(token == While, "something wrong here");
	BOOST_CHECK_MESSAGE(test_lexer.get_cur_token_val() == "while", "something wrong here");

	token = test_lexer.get_next_token();
	BOOST_CHECK_MESSAGE(token == Id, "something wrong here");
	BOOST_CHECK_MESSAGE(test_lexer.get_cur_token_val() == "id", "something wrong here");

	token = test_lexer.get_next_token();
	BOOST_CHECK_MESSAGE(token == 0, "something wrong here");



}