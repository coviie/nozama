/*
 * Parser.cpp
 * Written by: Max Bernstein and Erica Schwartz
 * Fall 2016
 *
 * Implements a Parser class that parses a Nozama input file and
 * returns each Order it specifies, one by one.
 *
 * Note:  Assumes input file is well-formed and ends in a new line.
 *        There is no provision for malformed files --- caveat emptor.
 */

#include <iostream>
#include <exception>

#include "Parser.h"
#include "Order.h"

/*
 * Non-default constructor: takes as argument the filename (as a string)
 * to be read in and parsed, and opens the file
 * Throws an exception (logic_error) if the file cannot be opened
 */
Parser::Parser(std::string &filename) {
        orders.open(filename);
        if (orders.fail()) {
                throw std::logic_error("Could not open file `"
                                       + filename + "'");
        }
        /*
         * Initialize cached order by reading in first order
         * The return value will be the uninitialized value of 
         * cached_order
         */
        (void) read_order();
}

/* Destructor: closes the file */
Parser::~Parser() {
        orders.close();
}

/*
 * Returns true if (and only if) the all orders have been read in.
 * We're assuming files end in a new line.
 */
bool Parser::is_done() const {
        return orders.eof();
}

/*
 * Reads one order from the file, and returns that order
 * Throws an exception (logic_error) if no orders remain to be read
 *
 * Note:  reads new order into cached_order, but returns previous
 *        value of cached_order.
 */
Order Parser::read_order() {
        if (is_done()) {
                throw std::logic_error("Parser:  End of file encountered.");
        }

        Order order = cached_order;
        std::string s;

        /* 
         * order cached_order.id arrived at
         * time cached_order.arrival_timestamp
         */
        orders >> s >> cached_order.id >> s >> s >> s
               >> cached_order.arrivalTime;

        /* fetch time cached_order.fetch_duration minutes, */
        orders >> s >> s >> cached_order.fetchTime >> s;

        /* pack time cached_order.pack_duration minutes */
        orders >> s >> s >> cached_order.packTime >> s;

        cached_order.fetchTimeLeft = cached_order.fetchTime;
        cached_order.packTimeLeft  = cached_order.packTime;

        return order;
}

