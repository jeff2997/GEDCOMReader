###############################################################
# Program:
#     Week 13, Hash
#     Brother Ercanbrack, CS235
# Author:
#     Jeff Pearson
# Summary:
#     PARSES AND DISPLAYS A GEDCOM FILE!!!!!!!
###############################################################

##############################################################
# The main rule
##############################################################
a.out: main.o familytree.o
	g++ -o a.out main.o familytree.o -std=c++11
	tar -cvf week13.tar .

##############################################################
# The individual components
#      main.o
#      familytree.o
##############################################################
main.o: main.cpp familytree.h jtl/list.h
	g++ -c main.cpp -g -std=c++11
###################################
#
#
###################################
familytree.o: familytree.cpp jtl/vector.h
	g++ -c familytree.cpp -g -std=c++11
