###########################################################################
##                         Makefile for Nozama                           ##
###########################################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11
LDFLAGS  = -g3

RPNCalc: Parser.o Orderqueue.o string2int.o FetchUnit.o PackerUnit.o \
		Simulation.o main.o
	${CXX} ${LDFLAGS} -o simulation Parser.o Orderqueue.o string2int.o \
				FetchUnit.o PackerUnit.o Simulation.o main.o

Parser.o:  	Parser.h 	Parser.cpp 
Orderqueue.o:	Orderqueue.h	Orderqueue.cpp
string2int.o:	string2int.h	string2int.cpp
FetchUnit.o:	FetchUnit.h	FetchUnit.cpp
PackerUnit.o:	PackerUnit.h	PackerUnit.cpp
Simulation.o:	Simulation.h	Simulation.cpp
main.o:		main.cpp	Order.h		Orderqueue.h	Parser.h \
		FetchUnit.h 	Simulation.h 	string2int.h

clean:
	rm -rf simulation *.o *.dSYM