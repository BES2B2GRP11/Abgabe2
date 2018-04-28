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

all: clean $(SUBDIRS)
	$(MAKE) -C src

clean:
	$(MAKE) $@ -C src
	$(MAKE) $@ -C test

test: clean all
	$(MAKE) -C test 

dist-check:
	mkdir check-$(DIST_DIR)
	cp -r $(SRC_DIR) $(TEST_DIR) doxygen.cfg Makefile check-$(DIST_DIR)
	sed -i -e s/DDEBUG/DNDEBUG/g check-$(DIST_DIR)/src/Makefile
	cd check-$(DIST_DIR) && make test && make clean
	rm -rf check-$(DIST_DIR)

dist: distclean dist-check
	mkdir $(DIST_DIR)
	cp -r $(SRC_DIR) $(TESTDIR) doxygen.cfg Makefile $(DIST_DIR)
	sed -i -e s/DDEBUG/DNDEBUG/g $(DIST_DIR)/src/Makefile
	$(ZIP) $(DISTNAME) $(DIST_DIR) 1> /dev/null &&\
		$(RM) -rf $(DIST_DIR) || echo "Could not create the tarball $(DISTNAME)"
	@echo "Dist is ready to ship @ $(DISTNAME)"

distclean: clean
	$(RM) -rf $(DOC_DIR) $(DIST_DIR) $(DISTNAME) check-$(DIST_DIR) $(TARBALL)

doxy dox doc: $(SUBDIRS)
	doxygen doxygen.cfg 1> /dev/null

.PHONY: all clean distclean dist
