CC = gcc
CFLAGS = -Wall -lpthread -lm -lrt
OBJFILES = psp.o shared.o
ECHO = echo "going to build $@..."

OUTPUT = psp factor

all: $(OUTPUT)

psp: psp.o shared.o
	$(ECHO)
	$(CC) -o $@ $^ $(CFLAGS)	
		

psp.o: psp.c
	$(ECHO)
	$(CC) $(CFLAGS) -c $< -o $@

factor: factor.o shared.o
	$(ECHO)
	$(CC) -o $@ $^ $(CFLAGS)

factor.o: factor.c
	$(ECHO)
	$(CC) $(CFLAGS) -c $< -o $@		
	
shared.o: shared.c
	$(ECHO)
	$(CC) $(CFLAGS) -c shared.c
