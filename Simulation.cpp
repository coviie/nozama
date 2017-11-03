/*
 *  Simulation.cpp
 *  Simulation Implementation
 *  	   Written by : Jia Wen Goh
 *                 On : 01-03-2017
 * 
 *  Class that runs the Nozama simulation; in charge of time & transfer of 
 *  Orders
 */

#include <iostream>
#include <string>
#include "Order.h"
#include "Orderqueue.h"
#include "FetchUnit.h"
#include "PackerUnit.h"
#include "Parser.h"
#include "string2int.h"
#include "Simulation.h"
using namespace std;

/******************************** 
 * Constructors and Destructors *
 ********************************/
/* [Name]:		Simulation
 * [Purpose]:		Constructor; Initializes the start of time, and a
 *			dynamic array of Packers based on the input of the
 * 			user
 * [Parameters]:	1 int (number of packers indicated by the user)
 * [Returns]:		-
 */
Simulation::Simulation(int numPackagingUnits)
{
	time = 0;
	numOfPackers = numPackagingUnits;
	packQueue = new PackerUnit[numOfPackers];
}

/* [Name]:		~Simulation
 * [Purpose]:		Destructor; Deletes the heap-allocated data (of 
			the dynamic array of PackerUnits) 
 * [Parameters]:	-
 * [Returns]:		-
 */
Simulation::~Simulation()
{
	delete []packQueue;
}

/*******************************
 *     Simulation Functions    *
 *******************************/

/* [Name]:		run
 * [Purpose]:		Runs the simulation; Governs the simulation time.  
 * [Parameters]:	1 int (minimum time out of all Orders)
 * [Returns]:		void
 */
void Simulation::run(Orderqueue &masterQueue, string packerMode)
{
	int packerNum = 0;
	while (allOrdersProcessed(masterQueue) == false) {
		
		// masterQueue to fetchQueue
		masterToFetcher(masterQueue);
		
		// fetchQueue to packQueue
		packerNum = fetcherToPacker(packerMode, packerNum);
		
		// packQueue to finishedQueue
		packerToFinished();
	
		time++;
	}

	print();
}

/* [Name]:		allOrdersProcessed
 * [Purpose]:		Checks if all orders have been processed (all orders
 * 			have been sent to finishedQueue), meaning:
 *			- initial masterQueue is empty 
 *			- fetchQueue is empty 
 * 			- packerUnits are empty
 * [Parameters]:	1 Orderqueue& (masterQueue to be checked)
 * [Returns]:		bool (true if allOrdersProcessed, false if not)
 */
bool Simulation::allOrdersProcessed(Orderqueue &masterQueue)
{
	if (masterQueue.isEmpty() == true and fetchQueue.isEmpty() == true) {
		for (int i = 0; i < numOfPackers; i++) {
			if (packQueue[i].isEmpty() == false)
				return false;
		}
		return true;
	}
	else
		return false;
}

/******** Queue-to-Queue Transfer Functions ********/
/* [Name]:		masterToFetcher
 * [Purpose]:		Once an order arrives (i.e. the arrival time of
 * 			the front-most order in masterQueue is reached),
 * 			send the order to the fetchQueue.
 * [Parameters]:	1 Orderqueue& (masterQueue)
 * [Returns]:		void
 */
void Simulation::masterToFetcher(Orderqueue &masterQueue)
{
	if (masterQueue.isEmpty() == false and
		time == masterQueue.frontOrder().arrivalTime) {
			fetchQueue.receiveOrder(masterQueue.dequeue());
	}
}

/* [Name]:		fetcherToPacker
 * [Purpose]:		Once an Order is ready to be sent out of the fetcher,
 * 			send it to a packer (which packer it is sent to 
 * 			depends on the packerMode). 
 * [Parameters]:	1 string (packerMode) and 1 int (Number of the packer
 * 			the order should be sent to)
 * [Returns]:		int (the packer number that the next order will be 
 * 			sent to)
 */
int Simulation::fetcherToPacker(string packerMode, int packerNum)
{
	if (fetchQueue.checkTime() == true) {
		if (packerMode == "ROUND_ROBIN")
			return roundRobin(packerNum);
		else {
			shortestTime();
			return packerNum;
		}
	}
	return packerNum;
}

/* [Name]:		packerToFinished
 * [Purpose]:		Once an Order is ready to be sent out of any packer,
 * 			send it out to finishedQueue, and update the elapsed
 * 			time of the sent Order.
 * [Parameters]:	-
 * [Returns]:		void
 */
void Simulation::packerToFinished()
{
	for (int i = 0; i < numOfPackers; i++) {
		if (packQueue[i].checkTime() == true) {
			finishedQueue.enqueue(packQueue[i].
				sendOrder());
			updateTimeSpent(time);
			packQueue[i].checkTime();
		}
	}
}

/******** Packer Mode Functions ********/
/* [Name]:		packTimeLeft
 * [Purpose]:		(Used mainly for debugging): Prints out the time
 * 			remaining to pack all Orders in all packerUnits
 * [Parameters]:	-
 * [Returns]:		void
 */
void Simulation::packTimeLeft()
{
	for (int i = 0; i < numOfPackers; i++) {
		cout << "Packer " << i << " time remaining: "
		     << packQueue[i].timeRemaining() << endl;
	}
	cout << endl;
}

/*---- Round Robin ----*/
/* [Name]:		roundRobin
 * [Purpose]:		Sends the Order from the fetchQueue to a packerUnit 
 * 			in a round robin style (i.e 0 -> 1 -> 2 -> 0 -> 1...)
 * [Parameters]:	1 int (packer that the Order should be sent to)
 * [Returns]:		int (next packer in line)
 */
int Simulation::roundRobin(int packerNum)
{
	packQueue[packerNum].receiveOrder(fetchQueue.sendOrder());
	fetchQueue.checkTime();
	return (packerNum + 1) % numOfPackers;	
}

/*---- Shortest Time ----*/
/* [Name]:		shortestTime
 * [Purpose]:		Sends the Order from the fetchQueue to the packerUnit
 * 			that has the shortest pack time remaining to pack 
 * 			existing Orders.
 * [Parameters]:	-
 * [Returns]:		void
 */
void Simulation::shortestTime()
{
	int packerNum = pingPackers();
	packQueue[packerNum].receiveOrder(fetchQueue.sendOrder());
	fetchQueue.checkTime();
}

/* [Name]:		pingPackers
 * [Purpose]:		Pings each packerUnit and determines which packerUnit 
 * 			has the shortest pack time remaining.
 * [Parameters]:	-
 * [Returns]:		int (packer that has the shortest pack time remaining)
 */
int Simulation::pingPackers()
{
	int shortestPacker = 0;
	int shortestTimeLeft = -1;
	for (int i = 0; i < numOfPackers; i++) {
		// If time remaining is smaller, set that as the shortest q
		if(packQueue[i].timeRemaining() < shortestTimeLeft or 
			shortestTimeLeft < 0) {
			shortestPacker = i;
			shortestTimeLeft = packQueue[i].timeRemaining();
		}
	}
	return shortestPacker;
}

/******** Time Functions ********/
/* [Name]:		updateTimeSpent
 * [Purpose]:		Updates elapsed time of the Order that leaves
 * 			the packer
 * [Parameters]:	1 int (time that the Order is sent out)
 * [Returns]:		void
 */
void Simulation::updateTimeSpent(int timeOfFinish)
{
	Order *curr = finishedQueue.orderDetailsBack();
	int timeOfArrival = curr->arrivalTime;
	curr->timeSpent = timeOfFinish - timeOfArrival;
}

/*******************************
 *       Print Functions       *
 *******************************/

/* [Name]:		print
 * [Purpose]:		Prints the details (arrival time, fetch time, pack 
 *			time, elapsed time, min/max/mean elapsed time) of all 
 *			orders. 
 *			Calls various helper functions (detailed below).
 * [Parameters]:	-
 * [Returns]:		void
 */
void Simulation::print()
{
	int size = finishedQueue.sizeOf();
	int min = -1;
	int max = 0;
	int total = 0;
	for (int currIndex = 0; currIndex < size; currIndex++) {
		Order *curr = finishedQueue.orderDetails(currIndex);
		printDetails(curr);
		total += curr->timeSpent;
		min  = calculateMin(curr, min);
		max  = calculateMax(curr, max);
	}
	printMin(min);
	printMax(max);
	printMean(total, size);
	cout << size << " orders processed\n";
}

/******** Calculation Functions ********/
/* [Name]:		calculateMin
 * [Purpose]:		Calculates the min elapsed time 
 * [Parameters]:	1 Order* (Order calculated), 1 int (elapsed time)
 * [Returns]:		int (min elapsed time)
 */
int Simulation::calculateMin(Order *curr, int min)
{
	if (curr->timeSpent < min or min < 0)
		return curr->timeSpent;
	else
		return min;
}

/* [Name]:		calculateMax
 * [Purpose]:		Calculates the max elapsed time 
 * [Parameters]:	1 Order* (Order calculated), 1 int (elapsed time)
 * [Returns]:		int (max elapsed time)
 */
int Simulation::calculateMax(Order *curr, int max)
{
	if (curr->timeSpent > max)
		return curr->timeSpent;
	else
		return max;
}

/******** Print Functions ********/
/* [Name]:		printDetails
 * [Purpose]:		Prints the time an Order took 
 * [Parameters]:	1 Order* (Order that will have its details printed)
 * [Returns]:		void
 */
void Simulation::printDetails(Order *curr)
{
	cout << "<Order(" << curr->id << ") "
	     << "arrival_timestamp = " 
	     << curr->arrivalTime << " "
	     << "fetch_duration = " 
	     << curr->fetchTime << " "
	     << "pack_duration = " 
	     << curr->packTime << " "
	     << "total_time = " 
	     << curr->timeSpent
	     << ">\n";
}

/* [Name]:		printMin
 * [Purpose]:		Prints the min elapsed time  
 * [Parameters]:	1 int (minimum time out of all Orders)
 * [Returns]:		void
 */
void Simulation::printMin(int min)
{
	cout << "min elapsed time " << min << " minutes\n";
}

/* [Name]:		printMax
 * [Purpose]:		Prints the max elapsed time  
 * [Parameters]:	1 int (maximum time out of all Orders)
 * [Returns]:		void
 */
void Simulation::printMax(int max)
{
	cout << "max elapsed time " << max << " minutes\n";
}

/* [Name]:		printMean
 * [Purpose]:		Prints the mean elapsed time  
 * [Parameters]:	2 ints (total time & number of Orders)
 * [Returns]:		void
 */
void Simulation::printMean(int total, int size)
{
	cout << "mean elapsed time " << total/size << " minutes\n";
}