#
# =====================================================================================
#
#       Filename:  Makefile
#
#    Description:  Actual makefile for examples
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
OBJECTS=fork.o exec.o
DEPS=fork.h fork.c exec.c exec.h
CFLAGS= -Wall -pedantic -Werror -Wextra -Wstrict-prototypes -Wformat=2 -fno-common -ftrapv -g -O3 -std=gnu11

%.o: %.c $(DEPS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

all: fork exec

fork: fork.o
	$(CC) $(CPPFLAGS) $(CFLAGS) -o forkexample fork.o

exec: exec.o
	$(CC) $(CPPFLAGS) $(CFLAGS) -o execexample exec.o

clean:
	$(RM) *.o *~ $(BIN)

.PHONY: clean

