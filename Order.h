/*
 * Order.h
 * Written by: Max Bernstein and Erica Schwartz
 * Fall 2016
 *
 * Defines an Order struct that holds the data for a Nozama order
 */

#ifndef ORDER_H
#define ORDER_H

struct Order {
        int id;			// Order ID
        int arrivalTime;	// Time of arrival
        int fetchTime;   	// Time to fetch
        int packTime;		// Time to pack
        int fetchTimeLeft;	// Time left to fetch
        int packTimeLeft;	// Time left to pack
	int timeSpent;		// Time spent in transit (i.e. pack & fetch)
};

#endif
