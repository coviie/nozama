/*
 *  main.cpp
 *  	   Written by : Jia Wen Goh
 *                 On : 01-03-2017
 * 
 *  Main that does checks (if user's cmd line input is valid), and if 
 *  the input file is valid (i.e. not empty). After which, it creates a 
 *  Simulation object that runs Nozama simulation.
 */

#include <iostream>
#include <string>
#include "Simulation.h"
#include "Order.h"
#include "Parser.h"
#include "string2int.h"
#include "Orderqueue.h"
#include "FetchUnit.h"
#include "PackerUnit.h"
using namespace std;

// Checks if user's cmd line input is valid
void validationChecks(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	validationChecks(argc, argv);
	
	string 	filename 	= argv[1];
	int	numOfPackers 	= string2int(argv[2]);
	string 	packerMode 	= argv[3];
	
	Parser 		parse(filename);
	Orderqueue	masterQueue;
	
	while (!parse.is_done()) {
		Order input = parse.read_order();
		masterQueue.enqueue(input);
	}
	
	if (masterQueue.isEmpty())
		throw(runtime_error("Empty input file."));

	
	Simulation main(numOfPackers);
	main.run(masterQueue, packerMode);
}


/* [Name]:		validationChecks
 * [Purpose]:		Checks if the user's command line input has the right 
 * 			number of inputs (4), if the packer mode is 
 * 			valid, and if there are >0 packers.
 * 			A runtime_error exception is thrown if anything 
 * 			is invalid.
 * [Parameters]:	1 int (argc), 1 char* (argv)
 * [Returns]:		void
 */
void validationChecks (int argc, char *argv[])
{
	// Valid format, i.e. 
	// ./simulation <filename> <num of packers> <packer mode>
	if (argc != 4)
		throw(runtime_error("Invalid input. Format should be: "
			"./simulation <filename> <num of packers> <packer " 
			"mode>"));

	// Valid packer mode
	if (std::string(argv[3]) != "ROUND_ROBIN" and 
	    std::string(argv[3]) != "SHORTEST_TIME")
		throw(runtime_error("Invalid Packer Mode input. "
			"Input 'ROUND_ROBIN' or 'SHORTEST_TIME'."));
	
	// >0 packers
	int numPackers = string2int(argv[2]);
	if (numPackers <= 0)
		throw(runtime_error("Invalid input. Please have at least "
			"1 packer."));
}