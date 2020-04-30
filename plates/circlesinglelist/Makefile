CXX=g++
CXXFLAGS=-g -Wall

###############################################################################
# Driver
###############################################################################

driver:	driver.cpp	circlesinglelist.o
	${CXX} ${CXXFLAGS} driver.cpp circlesinglelist.o -o driver

###############################################################################
# CircleSingleList
###############################################################################

circlesinglelist.o:	circlesinglelist.cpp circlesinglelist.h
	${CXX} ${CXXFLAGS} -c circlesinglelist.cpp -o circlesinglelist.o

###############################################################################
# Clean
###############################################################################

clean:
	rm -f *.o driver
