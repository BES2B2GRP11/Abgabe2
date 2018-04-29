#
# =====================================================================================
#
#       Filename:  Makefile
#
#    Description:  Template Makefile 
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
##
## @file Makefile
## Betriebssysteme popen / pclose Makefile
## Abgabe 2
##
## @author Ovidiu - Dan Bogat [ic17b501]
## @date 2018/04/10
##
## @version $Revision: 1.0.0$
##
## @todo Nothing much
##
## Last Modified: $Author: Ovidiu $
##
##

CC=gcc52
SUBDIRS=src
RM=rm
CFLAGS=-Wall -pedantic -Werror -Wextra -Wstrict-prototypes -Wformat=2 -fno-common -ftrapv -g -O3 -std=gnu89
SRC_DIR=src
EXAMPLE_DIR=examples
DOC_DIR=doc
TEST_DIR=test
DIST_DIR=bes2_grp11
DISTNAME="$(DIST_DIR).zip"
TARBALL=$(DIST_DIR).tar.bz2
TAR=tar -cvjf
ZIP=zip -r
SUBSCRIPT=/usr/local/bin/FHCheckSubmission.py
LIBS=libmypopen.a
LDFLAGS=-lmypopen
OBJECTS=mypopen.o

%.o: %.c $(DEPS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

all: clean $(OBJECTS)
	ar -cqv $(LIBS) $(OBJECTS)

clean:
	@-rm -rf *.{a,o} *~ $(LIBS) $(RM) $(BIN) ./popentest ./test-pipe $(DOC_DIR)

test-pipe:
	$(CC) -o test-pipe $(OBJECTS) -ltest-pipe &&\
./test-pipe

popentest:
	$(CC) -o popentest $(OBJECTS) -lpopentest -ldl &&\
./popentest $$nr

test: clean all popentest

doxy dox doc: 
	doxygen doxygen.dcf 1> /dev/null

.PHONY: all clean distclean dist test
