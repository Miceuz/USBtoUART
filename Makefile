###########################################
# Simple Makefile for HIDAPI test program
#
# Alan Ott
# Signal 11 Software
# 2010-07-03
###########################################

all: mcp2200

CC=gcc
CXX=g++
COBJS=mcp2200.o
OBJS=$(COBJS)
CFLAGS+=-Ihidapi/hidapi -Wall -g -c 
LIBS=-framework IOKit -framework CoreFoundation hidapi/mac/hid.o


mcp2200: $(OBJS)
	g++ -Wall -g $^ $(LIBS) -o mcp2200

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o hidtest $(CPPOBJS)

.PHONY: clean
