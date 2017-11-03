/*
 *  PackerUnit.h
 *  PackerUnit Class Header & Definitions
 *  	   Written by : Jia Wen Goh
 *                 On : 21-02-2017
 * 
 *  Packer unit - packs the order and sends it to the finishedQueue after 
 *  elapsed time.
 */

#ifndef PACKAGINGUNIT_H_
#define PACKAGINGUNIT_H_

#include "Order.h"
#include "Orderqueue.h"

class PackerUnit {
	private:
		/******************************** 
		 *     Packer Variables/Funcs   *
		 ********************************/
		// Packer 'foundation' - an Orderqueue
		Orderqueue	queue;
		
		// Decreases the packTimeLeft after 1 unit of time
		void 	decreasePackTime();
		
	public:
		/******************************** 
		 * Constructors and Destructors *
		 ********************************/
		// Initializes a PackerUnit (already initialized)
		PackerUnit();
		
		// Deletes heap-allocated data (nothing to be deleted)
		~PackerUnit();
		
		/******************************** 
		 *       Packer Functions       *
		 ********************************/
		// Receives (enqueues) an order from fetchUnit
		void	receiveOrder(Order);
		
		// Sends (dequeues) an order to finishedQueue
		Order	sendOrder();
		
		// Checks if the packer is empty; return true if it is, false
		// if not
		bool	isEmpty();
		
		// Logic-gate function that checks if the packer needs to push 
		// out an Order
		bool	checkTime();
		
		// Returns how much time the packer needs to finish packing
		// all its Orders
		int	timeRemaining();
};

#endif