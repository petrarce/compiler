#include <iostream>
#include <regex>
using namespace std;

int main(int argc, char** argv)
{
	string str(argv[1]);
	std::regex comment_regex("[0-9]\(.[0-9]\)", std::regex_constants::basic);
	if(regex_match(str, comment_regex))
		cout << "this is a comment" << endl;
	else
		cout << "this is NOT a comment" << endl;

	return 0;
}