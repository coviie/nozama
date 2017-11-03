#include <iostream>
#include <string>
#include "Order.h"
#include "Parser.h"
#include "string2int.h"
#include "Orderqueue.h"
using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 4)
		cerr << "Error input.\n";

	string 	filename = argv[1];
	int	numOfPackers = string2int(argv[2]);
	string 	packerMode = argv[3];
	
	Parser 		parse(filename);
	Orderqueue	masterQueue;
	
	while (!parse.is_done()) {
		Order input = parse.read_order();
		masterQueue.enqueue(input);
	}
	
	masterQueue.print();
}