# Makefile for assignment no. #1
CC = gcc
CFLAGS = -g -Wall
OBJFILES = hello.o \
	   first.o \
	   last.o \
	   color.o
OS := $(shell uname)
ifneq (,$(findstring CYGWIN_NT,$(OS)))
  EXT = .exe
else
  EXT =
endif

OUTPUT = myhello$(EXT)
ECHO = 	@echo going to build $@...
#TIME := $(shell date)
#blah:
#	@echo blah
#	@echo time is: $(TIME)
			
all: $(OUTPUT) test

hello.o: hello.c hello.h color.h
	echo going to compile hello.c...  # this line is just for demo
	$(CC) $(CFLAGS) -c hello.c

first.o: first.c
	echo going to compile first.c...  # this line is just for demo
	$(CC) $(CFLAGS) -c first.c

last.o: last.c 
	echo going to compile last.c...  # this line is just for demo
	$(CC) $(CFLAGS) -c last.c

color.o: color.c color.h
	$(ECHO) color.c
	$(ECHO) color.c  # this line is just for demo
	$(CC) $(CFLAGS) -c  color.c


$(OUTPUT): $(OBJFILES)
	@echo "OS is $(OS)  EXT is $(EXT)"  # only for the demo or debugging
	@echo $$^ is: $^
	$(ECHO)  
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -v *.o $(OUTPUT)

test:
	./myhello < test.in > test.out
	cat test.out
