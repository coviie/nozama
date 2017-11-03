/*
 * Parser.h
 * Written by: Max Bernstein and Erica Schwartz
 * Fall 2016
 *
 * Defines a Parser class that parses a Nozama input file and
 * returns each Order it specifies, one by one.
 */

#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include "Order.h"

/*
 * Parses a Nozama input file and returns the orders it contains, one by one
 *
 * Usage:
 *
 * To create the parser:
 * Parser p(filename);
 *
 * To read in the orders (pseudocode):
 * while (!p.is_done()) {
 *     Order order = p.read_order();
 *     // do something with order
 * }
 *
 * NOTE: This parser assumes the input file is well-formed.
 * It makes no guarantees for how it handles a poorly-formed input file.
 * Feel free to change this code as you see fit.
 *
 * This file assumes that there is a newline after the last order
 * in the file.
 */

class Parser {
public:
        Parser(std::string &filename);

        ~Parser();

        bool is_done() const;

        Order read_order();

private:
        /*
         * Require use of non-default constructor by making
         * default constructor private.
         */
        Parser();

        std::ifstream orders;
        Order          cached_order;
};

#endif
