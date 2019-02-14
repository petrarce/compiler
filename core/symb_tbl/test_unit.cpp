#define BOOST_TEST_MODULE SYMBOL_TABLE_MOD
#include <boost/test/included/unit_test.hpp>
#include <stbl.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(STBL_check_symbol_table)
{
	stbl& tbl_other = *stbl::get_instance(512);
	tbl_other.add_entry("id1", "int");
	tbl_other.add_entry("id2", "real");
	tbl_other.add_entry("id3", "float");

	stbl& tbl = *stbl::get_instance(1080);


	stbl_entry* entry = tbl.find_entry("id1");
	BOOST_REQUIRE_MESSAGE(entry, "something wrong with symbol table");
	BOOST_CHECK_MESSAGE(entry->id == "id1", "entry entry->id=" << entry->id << "instead of id1");
	BOOST_CHECK_MESSAGE(entry->type == "int", "entry entry->type=" << entry->type << "instead of int");
	entry = NULL;



	tbl.del_entry("id1");
	entry = tbl.find_entry("id1");
	BOOST_CHECK_MESSAGE(!entry, "something wrong here");
	entry == NULL;

	entry = tbl.find_entry("id2");
	BOOST_CHECK_MESSAGE(entry, "something wrong with symbol table");
	entry = NULL;

	entry = tbl.find_entry("id3");
	BOOST_CHECK_MESSAGE(entry, "something wrong with symbol table");
	entry = NULL;

}