CC=gcc
INSTCMD=install -m 0755 -s
PROG=electrotest
LIBDIR=/usr/lib
EXECDIR=/usr/bin
DEBUG=$(MAIN_DEBUG)
CFLAGS=-Wall -fPIC -std=c99 $(DEBUG)
LIBCFLAGS=$(CFLAGS) --shared
LDFLAGS=-L ./lib -Wl,-rpath=./lib
LIBS=-lcomponent -lpower -lresistance
LIBOBJS=component.so power.so resistance.so

.PHONY: all
all: lib program

program: main.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROG) main.o $(LIBS)

main.o: main.c resistance.h power.h component.h
	$(CC) $(CFLAGS) -c main.c

.PRECIOUS: %.o

lib: MKLIBDIR $(LIBOBJS)

MKLIBDIR:
	mkdir -p lib

%.so: %.o
	$(CC) $(LIBCFLAGS) $< -o lib/lib$(basename $@).so

%.o: %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	-rm -rf *.o *.so $(PROG) lib

install:
	@$(foreach LIBOBJ,$(LIBOBJS),echo "Installing lib$(LIBOBJ) to $(LIBDIR)"; $(INSTCMD) lib/lib$(LIBOBJ) $(LIBDIR);)
	@echo "Copying $(PROG) to $(EXECDIR)"
	@$(INSTCMD) $(PROG) $(EXECDIR)

uninstall:
	@$(foreach LIBOBJ,$(LIBOBJS),echo "Deleting lib$(LIBOBJ) from $(LIBDIR)"; rm -f $(LIBDIR)/lib$(LIBOBJ);)
	@echo "Deleting $(PROG) from $(EXECDIR)"
	-@rm -f $(EXECDIR)/$(PROG)
