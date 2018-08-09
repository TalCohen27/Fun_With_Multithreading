#!/bin/bash
NAME="Tal Cohen"
ID=302529672
echo script written by $NAME id: $ID
echo -n Date:' '
date
echo Machine data - host is: `hostname` host id is: `hostid`
mkdir $ID
cp a/hello.c $ID/hello.c
cd $ID
sed -i s/student/"$NAME"/g hello.c
echo compiling hello.c
gcc -S hello.c
gcc -c hello.c
gcc -Wall -o hello hello.o
echo exit status of last command is: $?
./hello