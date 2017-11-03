/*
 *  Orderqueue.h
 *  Orderqueue Implementation
 *  	   Written by : Jia Wen Goh
 *                 On : 21-02-2017
 * 
 *  Class that contains the queue data structure that will be used
 *  by the various 'conveyer-belt' units of Nozama.
 */

#include <iostream>
#include "Order.h"
#include "Orderqueue.h"
using namespace std;

/*******************************
 * CONSTRUCTORS & DESCTRUCTORS *
 *******************************/

/* [Name]:		Orderqueue
 * [Purpose]:		Constructor; Initializes an empty queue
 * [Parameters]:	-
 * [Returns]:		-
 */
Orderqueue::Orderqueue()
{
	init();
}

/* [Name]:		Orderqueue
 * [Purpose]:		Constructor; Initializes a queue with an
 * 			input.
 * [Parameters]:	-
 * [Returns]:		-
 */
Orderqueue::Orderqueue(Order input)
{
	init();
	enqueue(input);
}

/* [Name]:		~Orderqueue
 * [Purpose]:		Destructor; Deletes the heap-allocated data (of 
			the queue) 
 * [Parameters]:	-
 * [Returns]:		-
 */
Orderqueue::~Orderqueue()
{
	delete []orderArray;
}

/******************************** 
 *     Public Queue Functions   *
 ********************************/

/* [Name]:		enqueue
 * [Purpose]:		Adds the given Order into the queue
 * [Parameters]:	1 Order (input)
 * [Returns]:		void
 */
void Orderqueue::enqueue(Order input)
{
	if (currentSize == capacity)
		expand();
	
	currentSize++;
	orderArray[back] = input;
	back = nextIndex(back);
}

/* [Name]:		dequeue
 * [Purpose]:		Removes the front-most Order and returns it
 * [Parameters]:	-
 * [Returns]:		Order (front-most Order removed)
 */
Order Orderqueue::dequeue()
{
	Order frontOrder = orderArray[front];
	front = nextIndex(front);
	currentSize--;
		
	return frontOrder;
}

/******************************** 
 *       Other Functions        *
 ********************************/

/* [Name]:		isEmpty
 * [Purpose]:		Checks if the queue is empty
 * [Parameters]:	-
 * [Returns]:		bool (true if empty, false if not)
 */
bool Orderqueue::isEmpty()
{
	if (currentSize == 0)
		return true;
	else
		return false;
}

/* [Name]:		sizeOf
 * [Purpose]:		Returns the number of Orders in the queue
 * [Parameters]:	-
 * [Returns]:		int (size)
 */
int Orderqueue::sizeOf()
{
	return currentSize;
}

/* [Name]:		getFront
 * [Purpose]:		Returns the front index of the queue
 * [Parameters]:	-
 * [Returns]:		int (front index)
 */
int Orderqueue::getFront()
{
	return front;
}

/* [Name]:		getBack
 * [Purpose]:		Returns the back index of the queue
 * [Parameters]:	-
 * [Returns]:		int (back index)
 */
int Orderqueue::getBack()
{
	return back;
}

/* [Name]:		frontOrder
 * [Purpose]:		Returns the front-most Order (but doesn't dequeue it)
 * [Parameters]:	-
 * [Returns]:		Order (front-most Order)
 */
Order Orderqueue::frontOrder()
{
	return orderArray[front];
}

/* [Name]:		orderDetails
 * [Purpose]:		Returns a pointer to the front-most Order
 * 			(does not dequeue it)
 * [Parameters]:	-
 * [Returns]:		Order ptr
 */
Order *Orderqueue::orderDetails()
{
	return &(orderArray[front]);
}

/* [Name]:		orderDetailsBack
 * [Purpose]:		Returns a pointer to the back-most Order
 * 			(does not dequeue it)
 * [Parameters]:	-
 * [Returns]:		Order ptr
 */
Order *Orderqueue::orderDetailsBack()
{
	return &(orderArray[prevIndex(back)]);
}

/* [Name]:		orderDetails
 * [Purpose]:		Returns a pointer to the indexed Order
 * 			(does not dequeue it)
 * [Parameters]:	1 int (index)
 * [Returns]:		Order ptr
 */
Order *Orderqueue::orderDetails(int index)
{
	return &(orderArray[index % capacity]);
}

/******************************** 
 *    Private Queue Functions   *
 ********************************/

/* [Name]:		nextIndex
 * [Purpose]:		Gives the next index (wraps around if it reaches
 * 			the end of the queue)
 * [Parameters]:	1 int (index referenced)
 * [Returns]:		int (next-index)
 */
int Orderqueue::nextIndex(int index)
{
	return ((index + 1) % (capacity));
}

/* [Name]:		prevIndex
 * [Purpose]:		Gives the prev index (wraps around if it reaches
 * 			the front of the queue)
 * [Parameters]:	1 int (index referenced)
 * [Returns]:		int (prev-index)
 */
int Orderqueue::prevIndex(int index)
{
	if ((index - 1) < 0)
		return (capacity - 1);
	else
		return (index - 1);
}

/* [Name]:		expand
 * [Purpose]:		If capacity is reached, multiply the capacity value by
 * 			2 and update the queue
 * 			(i.e. double the capacity of that queue).
 * [Parameters]:	-
 * [Returns]:		void
 */
void Orderqueue::expand()
{
	Order *temp = new Order[capacity * 2];
	for (int i = 0; i < currentSize; i++) {
		temp[i] = orderArray[front];
		front = nextIndex(front);
	}
	front = 0;
	back = capacity;
	capacity *= 2;
	
	delete []orderArray;
	orderArray = temp;
}

/* [Name]:		init
 * [Purpose]:		Initializes an empty queue 
 * [Parameters]:	-
 * [Returns]:		void
 */
void Orderqueue::init()
{
	capacity      = INIT_CAPACITY;
        orderArray    = new Order[capacity];
        currentSize   = 0;
        front         = 0;
        back          = 0;
}

/* [Name]:		print
 * [Purpose]:		Prints out the stored Orders & their details
 *			USED FOR DEBUGGING 
 * [Parameters]:	-
 * [Returns]:		void
 *
void Orderqueue::print()
{
	for (int i = front; i < currentSize + front; i++) {
		cout << "**Order " << orderArray[i].id << "**\n";
		     << "\t Arrival time: " << orderArray[i].arrivalTime
		     << "\n\t Fetch time: " << orderArray[i].fetchTime
		     << "\n\t Fetch time left: " << orderArray[i].fetchTimeLeft
		     << "\n\t Pack time: " << orderArray[i].packTime
		     << "\n\t Pack time left: " << orderArray[i].packTimeLeft
		     << endl;
	}
}*/
