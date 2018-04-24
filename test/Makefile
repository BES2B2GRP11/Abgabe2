#
# =====================================================================================
#
#       Filename:  Makefile
#
#    Description:  Actual makefile for the sources
#
#        Version:  1.0.0
#        Created:  02/20/2018 09:40:05 AM
#       Revision:  none
#       Compiler:  gcc
#
#         Author:  Ovidiu - Dan Bogat [ic17b501], ic17b501@technikum-wien.at
# =====================================================================================
#
# DOXYGEN
#
##
## @file Makefile
## Eigentliches Makefile fuer die sources
## Beispiel 1
##
## @author Ovidiu - Dan Bogat [ic17b501]
## @date 2018/02/19
##
## @version $Revision: 1.0.0$
##
## @todo
##
## Last Modified: $Author: Ovidiu $
##
##

CC=gcc52
BIN=testsuite
OBJECTS=testsuite.o 
DEPS=testsuite.h
CFLAGS=-DDEBUG -Wall -pedantic -Werror -Wextra -Wstrict-prototypes -Wformat=2 -fno-common -ftrapv -g -O3 -std=gnu11
#CFLAGS= -Wall -pedantic -Werror -Wextra -Wstrict-prototypes -Wformat=2 -fno-common -ftrapv -g -O3 -std=gnu11
#CPPFLAGS=-I./../linux
LDFLAGS=-L./../src -lmypopen

%.o: %.c $(DEPS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

all: popentest

test-pipe: 
	$(CC) -o test-pipe ./../src/mypopen.o -ltest-pipe &&\
  ./test-pipe

popentest: 
	$(CC) -o popentest ./../src/mypopen.o -lpopentest -ldl &&\
  ./popentest $$nr

clean:
	$(RM) *.o *~ $(BIN) ./popentest ./test-pipe

.PHONY: clean

