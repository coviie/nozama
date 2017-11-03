/*
 *  Orderqueue.h
 *  Orderqueue Class Header & Definitions
 *  	   Written by : Jia Wen Goh
 *                 On : 21-02-2017
 * 
 *  Class that contains the queue data structure that will be used
 *  by the various 'conveyer-belt' units of Nozama.
 */

#ifndef ORDERQUEUE_H_
#define ORDERQUEUE_H_

#include "Order.h"

class Orderqueue {
	private:
		// Constant static int of the initial queue capacity
		static const int INIT_CAPACITY = 5;
		
		/******************************** 
		 *       Queue Variables        *
		 ********************************/
		// Order pointer that contains the queue/array
		Order	*orderArray;
		
		// Current count/size of the queue
		int	currentSize;
		
		// Capacity of the queue
		int	capacity;
		
		// Front & back index of the queue
		int	front;
		int	back;
		
		/******************************** 
		 *        Queue Functions       *
		 ********************************/
		// Gives the next/back index (used when adding/removing vars)
		int	nextIndex(int);
		int	prevIndex(int);
		
		// Expanding the queue if it reaches capacity
		void	expand();

		// Initializes an empty Orderqueue
		void	init();
		
	public:
		/******************************** 
		 * Constructors and Destructors *
		 ********************************/
		// Initializes an empty queue
		Orderqueue();
		
		// Initializes a queue with the input Order
		Orderqueue(Order);
		
		// Deletes heap-allocated data of the queue
		~Orderqueue();
		
		/******************************** 
		 *        Queue Functions       *
		 ********************************/
		// Adds the given Order into the queue
		void	enqueue(Order);
		
		// Removes the front-most Order and returns it
		Order	dequeue();
		
		/******************************** 
		 *       Other Functions        *
		 ********************************/
		// Checks if the queue is empty; return true if it is, false 
		// if not
		bool	isEmpty();
		
		// Returns the size of the queue
		int	sizeOf();
		
		// Returns the front/back index of the queue
		int	getFront();
		int	getBack();
		
		// Returns the front-most Order (does not dequeue it)
		Order	frontOrder();
		
		// Returns a pointer to the front-most Order (does not dequeue
		// it)
		Order	*orderDetails();
		
		// Returns a pointer to the back-most Order (does not dequeue
		// it)
		Order	*orderDetailsBack();
		
		// Returns a pointer to the indexed Order (does not dequeue it)
		Order	*orderDetails(int);
		
		// Used for debugging - Prints out stored Orders and their 
		// details 
		// void	print();
};

#endif