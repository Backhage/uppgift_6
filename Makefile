CC=gcc
INSTCMD=install -m 0755 -s
PROG=electrotest
#Detect if 64bit or 32bit system
#Solution for this detection from
#http://www.linuxquestions.org/questions/programming-9/how-can-make-makefile-detect-64-bit-os-679513/
SYSBITS=$(shell getconf LONG_BIT)
ifeq ($(SYSBITS),64)
LIBDIR=/usr/lib64
else
LIBDIR=/usr/lib
endif
#MAIN_DEBUG=-D _MAIN_DEBUG__
EXECDIR=/usr/bin
DEBUG=$(MAIN_DEBUG)
CFLAGS=-Wall -fPIC $(DEBUG)
LIBCFLAGS=$(CFLAGS) --shared
LDFLAGS=-L .
LIBS=-lcomponent -lpower -lresistance
LIBOBJS=component.so power.so resistance.so


all: lib program

program: main.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROG) main.o $(LIBS)

main.o: main.c resistance.h power.h component.h
	$(CC) -c main.c


.PRECIOUS: %.o

lib: $(LIBOBJS)

%.so: %.o
	$(CC) $(LIBCFLAGS) $< -o lib$(basename $@).so

%.o: %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	-rm -f *.o *.so $(PROG)

install:
	@$(foreach LIBOBJ,$(LIBOBJS),echo "Installing lib$(LIBOBJ) to $(LIBDIR)"; $(INSTCMD) lib$(LIBOBJ) $(LIBDIR);)
	@echo "Copying $(PROG) to $(EXECDIR)"
	@$(INSTCMD) $(PROG) $(EXECDIR)

uninstall:
	@$(foreach LIBOBJ,$(LIBOBJS),echo "Deleting lib$(LIBOBJ) from $(LIBDIR)"; rm -f $(LIBDIR)/lib$(LIBOBJ);)
	@echo "Deleting $(PROG) from $(EXECDIR)"
	-@rm -f $(EXECDIR)/$(PROG)
