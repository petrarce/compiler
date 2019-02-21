#include <iostream>
#include <vector>
#include <string>
#include <st_node.hpp>
using namespace std;

class semantic_analyser{
private:
	prog* st_root;

public:
	set_st_root(prog*);
	bool sem_check();

	semantic_analyser();
	~semantic_analyser();

}