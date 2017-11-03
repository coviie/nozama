#include <iostream>
#include <string>
#include "Order.h"
#include "Parser.h"
#include "string2int.h"
#include "Orderqueue.h"
using namespace std;

// Enqueues all the orders in the given file
void testEnqueue(Orderqueue&, Parser&);

// Prints all the orders in the queue
void print(Orderqueue&);

int main(int argc, char *argv[])
{
	if (argc != 3)
		throw(runtime_error("Invalid input."));
	
	string 	filename 	= argv[1];
	string	filename2	= argv[2];
	Parser 		parse(filename);
	Parser		parse2(filename2);
	Orderqueue	masterQueue;
	
	testEnqueue(masterQueue,parse);
	
	cout << "Dequeueing first 3 Orders. \n";
	for (int i = 0; i < 3; i++)
		masterQueue.dequeue();
	
	print(masterQueue);
	
	testEnqueue(masterQueue,parse2);
}

/* [Name]:		testEnqueue
 * [Purpose]:		Enqueues all the orders in the given file 
 * [Parameters]:	1 Orderqueue& (enqueueing into), 1 Parser 
 * [Returns]:		void
 */
void testEnqueue(Orderqueue &masterQueue, Parser &parse)
{
	while (!parse.is_done()) {
		Order input = parse.read_order();
		masterQueue.enqueue(input);
	}

	print(masterQueue);
}

/* [Name]:		print
 * [Purpose]:		Prints out the current stored orders 
 * [Parameters]:	1 Orderqueue&
 * [Returns]:		void
 */
void print(Orderqueue &masterQueue) 
{
	if (!masterQueue.isEmpty())
		cout << "Queue isn't empty.\n";
	
	cout << "-- Print -- \n" 
	     << "Size:\t" << masterQueue.sizeOf() << endl
	     << "Front Order id: " << masterQueue.orderDetails()->id << endl
	     << "Front Order id: " 
	     << masterQueue.orderDetails(masterQueue.getFront())->id << endl
	     << "Back Index: " << masterQueue.getBack() << endl
	     << "Back Order id: " << masterQueue.orderDetailsBack()->id 
	     << endl;
	
	//masterQueue.print();
	cout << endl;
}