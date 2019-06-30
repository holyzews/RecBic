VER=1.0
DIST=RecBic$(VER)
PROGS=RecBic
SRCS=struct.cpp read_array.cpp  get_options.cpp fib.cpp write_block.cpp  colbase.cpp main.cpp 
OBJS=$(SRCS:.cpp=.o) 
CC=g++


LDFLAGS= -lm -fopenmp
CPPFLAGS= -std=c++0x -g -fopenmp -Wall -I.  -DVER=$(VER)
OMPFLAGS=-fopenmp

all: $(PROGS)

${PROGS}: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

.o:
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(PROGS)
	rm -f *.o
	rm -f *.rules
	rm -f *.chars
	rm -f *.blocks
	rm -f *.expansion

dist:
	$(MAKE) clean
	cd .. && tar czvf $(DIST).tar.gz $(DIST)/

Ecoli.chars:
	./${PROGS} -i Ecoli

CRP.blocks:
	./${PROGS} -i CRP 

test: Ecoli.chars CRP.blocks
	./${PROGS} -i Ecoli.chars -b CRP.blocks -s
