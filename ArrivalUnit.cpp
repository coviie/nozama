#include <iostream>
#include "Order.h"
#include "Orderqueue.h"
#include "ArrivalUnit.h"
using namespace std;

ArrivalUnit::ArrivalUnit()
{
	
}

ArrivalUnit::~ArrivalUnit()
{
	
}

void ArrivalUnit::receiveOrder(Order input)
{
	queue.enqueue(input);
}

Order ArrivalUnit::sendOrder(Order output, int time)
{
	if (time = receivedOrder.)
}