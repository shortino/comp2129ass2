CC = gcc
CFLAGS = -g -O0 -pedantic -Wall -W -std=gnu99
LDFLAGS = 
TESTER = ~comp2129/assignment2/mark-sample

BINARIES = dw

.PHONY: all clean depends test

all: $(BINARIES)

clean:
	-rm -f *.o
	-rm -f $(BINARIES)

depends:
	$(CC) $(CFLAGS) -MM *.c > Makefile.depends

test: test_dw

dw: dw.o
	$(CC) $(LDFLAGS) $^ -o $@

test_dw: dw
	$(TESTER) question1 ./dw

-include Makefile.depends
