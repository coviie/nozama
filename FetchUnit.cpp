/*
 *  FetchUnit.cpp
 *  FetchUnit Implementation
 *  	   Written by : Jia Wen Goh
 *                 On : 01-03-2017
 * 
 *  Fetching unit - fetches the order and sends it to a packer after 
 *  elapsed time.
 */

#include <iostream>
#include "Order.h"
#include "Orderqueue.h"
#include "FetchUnit.h"
using namespace std;

/*******************************
 *  Constructors & Destructors *
 *******************************/

/* [Name]:		FetchUnit
 * [Purpose]:		Constructor (nothing needs to be initialized)
 * [Parameters]:	-
 * [Returns]:		-
 */
FetchUnit::FetchUnit()
{

}

/* [Name]:		~FetchUnit
 * [Purpose]:		Destructor (no heap-allocated data needs to be 
 * 			deleted)
 * [Parameters]:	-
 * [Returns]:		-
 */
FetchUnit::~FetchUnit()
{
	
}

/*******************************
 *  Public Fetcher Functions   *
 *******************************/

/* [Name]:		receiveOrder
 * [Purpose]:		Receives (enqueues) an Order from masterQueue
 * [Parameters]:	1 Order (input)
 * [Returns]:		void
 */
void FetchUnit::receiveOrder(Order input)
{
	queue.enqueue(input);
}

/* [Name]:		sendOrder
 * [Purpose]:		Sends (dequeues) an Order into a packerUnit
 * [Parameters]:	-
 * [Returns]:		Order (Order that is dequeued and sent)
 */
Order FetchUnit::sendOrder()
{
	return queue.dequeue();
}

/* [Name]:		isEmpty
 * [Purpose]:		Checks if the fetcher is empty
 * [Parameters]:	-
 * [Returns]:		bool (true if empty, false if not)
 */
bool FetchUnit::isEmpty()
{
	return queue.isEmpty();
}

/* [Name]:		checkTime
 * [Purpose]:		'Logic gate' that checks if the fetcher can/is ready
 * 			to push an order.
 * 				- If the fetcher is empty, nothing can be/is 
 * 				  sent (return false)
 * 				- Else if the first order (frontOrder) has 0
 * 				  fetchTimeLeft, send the Order (return true)
 * 				- Else, decreaseFetchTime, and send nothing
 * 				  (return false)
 * [Parameters]:	-
 * [Returns]:		bool (true/false based on conditions above)
 */
bool FetchUnit::checkTime()
{
	if (queue.isEmpty() == true)
		return false;
	else if (queue.frontOrder().fetchTimeLeft == 0)
		return true;
	else {
		decreaseFetchTime();
		return false;
	}
}

/*******************************
 *  Private Fetcher Functions  *
 *******************************/

/* [Name]:		decreaseFetchTime
 * [Purpose]:		Decreases fetchTimeLeft after 1 unit of time
 * [Parameters]:	-
 * [Returns]:		void
 */
void FetchUnit::decreaseFetchTime()
{
	Order *curr = queue.orderDetails();
	curr->fetchTimeLeft--;
}