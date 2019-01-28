#define BOOST_TEST_MODULE WHILE_LEXER
#include <boost/test/included/unit_test.hpp>
#include <lexer.hpp>

BOOST_AUTO_TEST_CASE(LEXER_test_tokenisation)
{
	lexer test_lexer(	"//comment1\n"
					 	"/*comment2////****/ "
						"int "
						"real "
						"if "
						"else "
						"while "
						"{ "
						"+ "
						"\"string literal\" "
						"123332 "
						"some_id1 ");

	vector<uint32_t> tokens_arr;
	vector<uint32_t> tokens_arr_expected = {
		Type, Type, If, Else, 
		While, '{', '+', Literal, Literal, Id };
	uint32_t token = test_lexer.get_next_token();
	while(token){
		tokens_arr.push_back(token);
		token = test_lexer.get_next_token();
	}

	if(tokens_arr != tokens_arr_expected){
		BOOST_ERROR("bas analysis!");
		printf("expected:\n");
		for(uint32_t i : tokens_arr_expected){
			printf("%d ", i);
		}
		printf("\nreceived:\n");
		for(uint32_t i : tokens_arr){
			printf("%d ", i);
		}
	}


}