#
# =====================================================================================
#
#       Filename:  Makefile
#
#    Description:  Actual makefile for the sources
#
#        Version:  1.0.0
#        Created:  04/10/2018 09:40:05 AM
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
BIN=myfind
OBJECTS=main.o myfind.o error_handling.o helpers.o dynchli.o
LIBS=plfmfind.a 
DEPS=main.h myfind.h error_handling.h helpers.h dynchli.h
#CFLAGS=-DDEBUG -Wall -pedantic -Werror -Wextra -Wstrict-prototypes -Wformat=2 -fno-common -ftrapv -g -O3 -std=gnu11
CFLAGS= -Wall -pedantic -Werror -Wextra -Wstrict-prototypes -Wformat=2 -fno-common -ftrapv -g -O3 -std=gnu11
CPPFLAGS=-I./../linux
LDFLAGS=-L./../linux -lplfmfind

%.o: %.c $(DEPS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

all: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(BIN) $^ $(LDFLAGS)

clean:
	$(RM) *.o *~ $(BIN)

.PHONY: clean

