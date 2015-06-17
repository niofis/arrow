CC=gcc-5
RM=rm -f
CFLAGS=-Wall -std=c99 -O2 -I../src -fopenmp #$(shell root-config --cflags)
LDFLAGS= #$(shell root-config --ldflags)
LDLIBS=-lm -fopenmp  #-lSDL2main #-Wl,-framework,Cocoa#$(shell root-config --libs)
VPATH=../src
SRCS=main.c
OPATH=../obj

#%.o : %.c
#	$(CC) $(CFLAGS) -c $< -o $(OPATH)/$@

OBJS=$(subst .c,.o,$(SRCS))

all: arrow

arrow: $(OBJS)
	$(CC) $(LDFLAGS) -o arrow $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
