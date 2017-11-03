#ifndef ARRIVALUNIT_H_
#define ARRIVALUNIT_H_

#include "Order.h"
#include "Orderqueue.h"

class ArrivalUnit {
	private:
		Orderqueue queue;
		Order receivedOrder;
		
	public:
		ArrivalUnit();
		~ArrivalUnit();
		
		void	receiveOrder(Order);
		Order	sendOrder(Order,int);
};

#endif