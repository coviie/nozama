/*
 *  PackerUnit.cpp
 *  PackerUnit Implementation
 *  	   Written by : Jia Wen Goh
 *                 On : 01-03-2017
 * 
 *  Packer unit - packs the order and sends it to the finishedQueue after 
 *  elapsed time.
 */

#include <iostream>
#include "Order.h"
#include "Orderqueue.h"
#include "PackerUnit.h"
using namespace std;

/*******************************
 *  Constructors & Destructors *
 *******************************/

/* [Name]:		PackerUnit
 * [Purpose]:		Constructor (nothing needs to be initialized)
 * [Parameters]:	-
 * [Returns]:		-
 */
PackerUnit::PackerUnit()
{
	
}

/* [Name]:		PackerUnit
 * [Purpose]:		Destructor (no heap-allocated data needs to be 
 * 			deleted)
 * [Parameters]:	-
 * [Returns]:		-
 */
PackerUnit::~PackerUnit()
{
	
}

/*******************************
 *   Public Packer Functions   *
 *******************************/

/* [Name]:		receiveOrder
 * [Purpose]:		Receives (enqueues) an Order from a fetchUnit
 * [Parameters]:	1 Order (input)
 * [Returns]:		void
 */
void PackerUnit::receiveOrder(Order input)
{
	queue.enqueue(input);
}

/* [Name]:		sendOrder
 * [Purpose]:		Sends (dequeues) an Order into the finishedQueue
 * [Parameters]:	-
 * [Returns]:		Order (Order that is dequeued and sent)
 */
Order PackerUnit::sendOrder()
{
	return queue.dequeue();
}

/* [Name]:		isEmpty
 * [Purpose]:		Checks if the packer is empty
 * [Parameters]:	-
 * [Returns]:		bool (true if empty, false if not)
 */
bool PackerUnit::isEmpty()
{
	return queue.isEmpty();
}

/* [Name]:		checkTime
 * [Purpose]:		'Logic gate' that checks if the packer can/is ready
 * 			to push an order.
 * 				- If the packer is empty, nothing can be/is 
 * 				  sent (return false)
 * 				- Else if the first order (frontOrder) has 0
 * 				  packTimeLeft, send the Order (return true)
 * 				- Else, decreasePackTime, and send nothing
 * 				  (return false)
 * [Parameters]:	-
 * [Returns]:		bool (true/false based on conditions above)
 */
bool PackerUnit::checkTime()
{
	if (queue.isEmpty() == true)
		return false;
	else if (queue.frontOrder().packTimeLeft == 0)
		return true;
	else {
		decreasePackTime();
		return false;
	}
}

/* [Name]:		timeRemaining
 * [Purpose]:		Returns how much time the packer needs to finish
 *			packing all its Orders 
 * [Parameters]:	-
 * [Returns]:		int (time needed to finish packing)
 */
int PackerUnit::timeRemaining()
{
	int timeLeft = 0;
	for (int i = 0; i < queue.sizeOf(); i++) {
		timeLeft += queue.orderDetails(i + 
				queue.getFront())->packTimeLeft;
	}
	return timeLeft;
}

/*******************************
 *   Private Packer Functions  *
 *******************************/

/* [Name]:		decreasePackTime
 * [Purpose]:		Decreases packTimeLeft after 1 unit of time
 * [Parameters]:	-
 * [Returns]:		void
 */
void PackerUnit::decreasePackTime()
{
	Order *curr = queue.orderDetails();
	curr->packTimeLeft--;
}