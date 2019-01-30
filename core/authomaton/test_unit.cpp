#define BOOST_TEST_MODULE ATOMATON_TEST
#include <nfa.hpp>
#include <boost/test/included/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(NFA_check_links)
{
	nfa test_nfa;
	string test;
	string required_str;

	test_nfa.link_state(0,'a',1);
	test = test_nfa.get_links();
	required_str = "0@a@1\\";
	BOOST_CHECK_MESSAGE(test == required_str, 
		"test=" << test << ", instead of " << required_str);

	test_nfa.link_state(0,"abcd",1);
	test = test_nfa.get_links();	
	required_str = "0@a@1\\0@b@1\\0@c@1\\0@d@1\\";
	BOOST_CHECK_MESSAGE(test == required_str, 
		"test=" << test << ", instead of " << required_str);

	test_nfa.link_state("0@abcd@1\\");
	test = test_nfa.get_links();	
	required_str = "0@a@1\\0@b@1\\0@c@1\\0@d@1\\";
	BOOST_CHECK_MESSAGE(test == required_str, 
		"test=" << test << ", instead of " << required_str);
	//test_nfa will be automatically destroyed after exit from function

}

BOOST_AUTO_TEST_CASE(NFA_check_accepting)
{
	nfa test_nfa;
	const vector<pair<uint32_t, SATOKENS>> res_expected = {
		{2, ID},
		{4, COMMENT}
	};

	test_nfa.link_state("0@@1\\1@a@2\\0@@3\\3@b@4\\");

	test_nfa.set_accepting(2,ID);
	test_nfa.set_accepting(4,COMMENT);

	vector<pair<uint32_t, SATOKENS>> res_obtained = test_nfa.get_accepting();
	sort(res_obtained.begin(), res_obtained.end());
	BOOST_CHECK_MESSAGE(res_obtained == res_expected, 
		"res_obtained = {" 	
		<< to_string(res_obtained[0].first) << to_string(res_obtained[1].first)
		<< "} instead of {" 	
		<< to_string(res_expected[0].first) << to_string(res_expected[1].first)
		<< "}");

}

BOOST_AUTO_TEST_CASE(NFA_check_convertions){
	nfa nfa1, nfa2;

	nfa1.link_state("0@a@1\\");
	nfa1.set_accepting(1,ID);
	nfa2.link_state("0@b@1\\");
	nfa2.set_accepting(1, COMMENT);
	string inp = "a";

	nfa test_nfa = nfa1;
	analyse_map_s* res_ptr = test_nfa.nfa_bt_next(inp);
	BOOST_REQUIRE_MESSAGE(res_ptr, "no analysis returned, however should");
	analyse_map_s res = *res_ptr;
	delete res_ptr;
	res_ptr = NULL;
	BOOST_CHECK_MESSAGE(res.analyse == ID, 
							"res=" 
							<< res.analyse 
							<<", instead of "
							<< ID);

	test_nfa.nfa_reset();
	inp = "b";
	res_ptr = test_nfa.nfa_bt_next(inp);
	if(res_ptr){ 
		delete res_ptr;
		BOOST_ERROR("returned valid analyse however should not!");
	}

	test_nfa = nfa::nfa_convert_clausure(nfa1);
	test_nfa.set_analyse(ID);
	inp = "aaaaaaaaaaa";
	res_ptr = test_nfa.nfa_bt_next(inp);
	BOOST_REQUIRE_MESSAGE(res_ptr, "no analysis returned, however should");
	res = *res_ptr;
	delete res_ptr;
	res_ptr = NULL;
	BOOST_CHECK_MESSAGE(res.analyse == ID, 
							"res=" 
							<< res.analyse 
							<<", instead of "
							<< ID);

	test_nfa = nfa::nfa_convert_union(nfa1, nfa2);
	inp = "a";
	res_ptr = test_nfa.nfa_bt_next(inp);
	BOOST_REQUIRE_MESSAGE(res_ptr, "no analysis returned, however should");
	res = *res_ptr;
	delete res_ptr;
	res_ptr = NULL;
	BOOST_CHECK_MESSAGE(res.analyse == ID, 
							"res=" 
							<< res.analyse 
							<<", instead of "
							<< ID);
	test_nfa.nfa_reset();
	inp = "b";
	res_ptr = test_nfa.nfa_bt_next(inp);
	BOOST_REQUIRE_MESSAGE(res_ptr, "no analysis returned, however should");
	res = *res_ptr;
	delete res_ptr;
	res_ptr = NULL;
	BOOST_CHECK_MESSAGE(res.analyse == COMMENT, 
							"res=" 
							<< res.analyse 
							<<", instead of "
							<< COMMENT);


	test_nfa = nfa::nfa_convert_concat(nfa1, nfa2);
	inp = "ab";
	test_nfa.set_analyse(ID);
	res_ptr = test_nfa.nfa_bt_next(inp);
	BOOST_REQUIRE_MESSAGE(res_ptr, "no analysis returned, however should");
	res = *res_ptr;
	delete res_ptr;
	res_ptr = NULL;
	BOOST_CHECK_MESSAGE(res.analyse == ID, 
							"res=" 
							<< res.analyse 
							<<", instead of "
							<< ID);



}

BOOST_AUTO_TEST_CASE(NFA_check_optimisation)
{

	nfa test_nfa;
	test_nfa.link_state("0@@1\\1@a@2\\2@b@3\\0@@5\\5@t@6\\6@r@7\\");

	string noptLinks = test_nfa.get_links();
	test_nfa.nfa_optimise();
	string optLinks = test_nfa.get_links();

	BOOST_CHECK_MESSAGE(optLinks == "0@a@1\\0@t@2\\1@b@3\\2@r@4\\", "something wrong here\n"
												<< "noptLinks: " << noptLinks << "\n"
												<< "optLinks: " << optLinks << "\n"	);

}
