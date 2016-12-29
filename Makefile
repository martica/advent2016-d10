IDIR =.
CC=gcc
CFLAGS=-I$(IDIR) -std=gnu99 -g

ODIR=obj
LDIR =.

LIBS=-lm

DEPS = ${wildcard *.h}

SOURCES := $(wildcard *.c)
OBJECTS  := $(SOURCES:%.c=$(ODIR)/%.o)

$(OBJECTS): $(ODIR)/%.o : %.c $(DEPS)
	    $(CC) $(CFLAGS) -c $< -o $@
	    @echo "Compiled "$<" successfully!"

d10: $(OBJECTS)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

valgrind: d10
	valgrind --leak-check=full --track-origins=yes ./d10

run: d10
	./d10
