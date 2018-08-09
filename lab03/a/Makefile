# Makefile for assignment no. #1

all: myhello.exe

hello.o: hello.c hello.h color.h
	echo going to compile hello.c...  # this line is just for demo
	gcc -Wall -c hello.c

first.o: first.c
	echo going to compile first.c...  # this line is just for demo
	gcc -Wall -c first.c

last.o: last.c 
	echo going to compile last.c...  # this line is just for demo
	gcc -Wall -c last.c

color.o: color.c color.h
	echo going to compile color.c...  # this line is just for demo
	gcc -Wall -c color.c


myhello: hello.o first.o last.o color.o		# on Linux the target should be myhello w/o the exe
	echo 'going to build (link) myhello...'		# this line is just for demo
	gcc -o myhello -Wall hello.o first.o last.o color.o

clean:
	rm *.o
	rm *.exe
	rm -v *.o myhello 
