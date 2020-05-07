CXX=g++
CXXFLAGS=-g -Wall

###############################################################################
# Driver
###############################################################################

driver:	driver.cpp	circledoublelist.o
	${CXX} ${CXXFLAGS} driver.cpp circledoublelist.o -o driver

###############################################################################
# CircleDoubleList
###############################################################################

circledoublelist.o:	circledoublelist.cpp circledoublelist.h
	${CXX} ${CXXFLAGS} -c circledoublelist.cpp -o circledoublelist.o

###############################################################################
# Clean
###############################################################################

clean:
	rm -f *.o driver
