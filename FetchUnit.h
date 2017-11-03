/*
 *  FetchUnit.h
 *  FetchUnit Class Header & Definitions
 *  	   Written by : Jia Wen Goh
 *                 On : 21-02-2017
 * 
 *  Fetching unit - fetches the order and sends it to a packer after 
 *  elapsed time.
 */

#ifndef FETCHUNIT_H_
#define FETCHUNIT_H_

#include "Order.h"
#include "Orderqueue.h"

class FetchUnit {
	private:
		/******************************** 
		 *    Fetcher Variables/Funcs   *
		 ********************************/
		// Fetcher 'foundation' - an Orderqueue
		Orderqueue	queue;
		
		// Decreases the fetchTimeLeft after 1 unit of time
		void 	decreaseFetchTime();
		
	public:
		/******************************** 
		 * Constructors and Destructors *
		 ********************************/
		// Initializes a FetchUnit (already initialized)
		FetchUnit();
		
		// Deletes heap-allocated data (nothing to be deleted)
		~FetchUnit();
		
		/******************************** 
		 *       Fetcher Functions      *
		 ********************************/
		// Receives (enqueues) an order from masterQueue
		void	receiveOrder(Order);
		
		// Sends (dequeues) an order to PackerUnit
		Order	sendOrder();
		
		// Checks if the fetcher is empty; return true if it is, false
		// if not
		bool	isEmpty();
		
		// Logic-gate function that checks if the fetcher needs to push 
		// out an Order
		bool	checkTime();
};

#endif