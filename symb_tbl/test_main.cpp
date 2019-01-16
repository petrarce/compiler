#include <stbl.hpp>

using namespace std;

int main(int argc, char** argv)
{
	stbl tbl(512);
	tbl.add_entry("id1", "int");
	tbl.add_entry("id2", "real");
	tbl.add_entry("id3", "float");

	stbl_entry* entry = tbl.find_entry("id1");
	tbl.del_entry("id2");
	assert(!entry);

	return 0;
}