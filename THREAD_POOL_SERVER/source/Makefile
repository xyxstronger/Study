.PHONY:clean install distclean

CC=gcc
TARGET=thread_pool_server
INCLUDE_PATH=../include
LIBRARY_PATH=../library
INSTALL_PATH=/usr/bin/
CFLAGS=-I$(INCLUDE_PATH) -g -Wall -c
CPPFLAGS=
LDFLAGS=-lpthread
SRCFILE=$(wildcard *.c)
DESFILE=$(patsubst %.c,%.o,$(SRCFILE))

$(TARGET):$(DESFILE)
	$(CC) $^ $(LDFLAGS) -o $@

%.o:%c
	$(CC) $(CFLAGS) $<

clean:
	rm $(DESFILE) -rf
	rm $(TARGET) -rf

install:

distclean:





