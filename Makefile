CC=gcc
INSTCMD=install -m 0755 -s
PROG=electrotest
#MAIN_DEBUG=-D _MAIN_DEBUG__
DEBUG=$(MAIN_DEBUG)
CFLAGS=-Wall -fPIC $(DEBUG)
LIBCFLAGS=$(CFLAGS) --shared
LDFLAGS=-L .
LIBS=-lcomponent -lpower -lresistance
LIBOBJS=component.so power.so resistance.so


all: lib program

program: main.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(PROG) main.o

main.o: main.c resistance.h power.h component.h
	$(CC) -c main.c


.PRECIOUS: %.o

lib: $(LIBOBJS)

%.so: %.o
	$(CC) $(LIBCFLAGS) $< -o lib$(basename $@).so

%.o: %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	-rm -f *.o *.so

install:
	@echo "Install not done"

uninstall:
	@echo "Uninstall not done"
