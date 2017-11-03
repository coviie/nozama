/*
 *  Simulation.h
 *  Simulation Class Header & Definitions
 *  	   Written by : Jia Wen Goh
 *                 On : 21-02-2017
 * 
 *  Class that runs the Nozama simulation; in charge of time & transfer of 
 *  Orders
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <iostream>
#include <string>
#include "Order.h"
#include "Orderqueue.h"
#include "FetchUnit.h"
#include "PackerUnit.h"
using namespace std;

class Simulation {
	private:
		/******************************** 
		 *     Simulation Variables     *
		 ********************************/
		// Fetcher Unit
		FetchUnit	fetchQueue;
		
		// Packer Units (a dynamic array of Packers will be created)
		// based on the number that the use specifies
		PackerUnit	*packQueue;
		
		// Finished queue (i.e. queue that collects all finished 
		// orders)
		Orderqueue	finishedQueue;
		
		// Simulation time
		int	time;
		
		// Number of packers user specifies
		int	numOfPackers;
		
		/******************************** 
		 *        Print Functions       *
		 ********************************/
		// Prints out the orders processed, and the time it took
		// for each step
		void	print();
		
		// -- Modular Functions --
		// Prints only the time it took
		void	printDetails(Order*);
		
		// Calculates min & max elapsed time
		int	calculateMin(Order*,int);
		int	calculateMax(Order*,int);
		
		// Prints min, max and mean elapsed time
		void	printMin(int);
		void	printMax(int);
		void	printMean(int,int);
		
		/******************************** 
		 *       Packer Functions       *
		 ********************************/
		// -- Queue-to-Queue Transfer Functions -- 
		// Sends an order from the masterQueue to fetchQueue
		// once arrived
		void	masterToFetcher(Orderqueue&);
		
		// Sends an order from the fetchQueue to a packerUnit
		// once fetched 
		int	fetcherToPacker(string,int);
		
		// Sends an order from a packerUnit to finishedQueue
		// once packed
		void	packerToFinished();
		
		/* ***** ROUND_ROBIN ***** */
		// Sends the order from Fetcher to Packer in a round robin
		// style. Returns the next Packer in line
		int	roundRobin(int);
		
		/* **** SHORTEST_TIME **** */
		// Sends the order from Fetcher to the Packer with the 
		// shortest pack time remaining to pack existing Orders
		void	shortestTime();
		
		// Pings each packer and returns which packer has the
		// shortest pack time remaining
		int	pingPackers();
		
		// Used for debugging - prints out the pack time remaining
		// for all packers
		void	packTimeLeft();
		
		// Function that is called by the run loop;
		// once all orders are processed, the run loop stops
		bool	allOrdersProcessed(Orderqueue&);
		
		// Updates elapsed time once the order leaves the packer
		void	updateTimeSpent(int);
		
	public:
		/******************************** 
		 * Constructors and Destructors *
		 ********************************/
		// Initializes a simulation
		Simulation(int);
		
		// Deletes heap-allocated data (i.e. dynamic array of
		// pack queues)
		~Simulation();
		
		/******************************** 
		 *     Simulation Functions     *
		 ********************************/
		// Runs the simulation, taking the masterQueue & packerMode
		// as parameters
		void	run(Orderqueue&,string);
};

#endif
