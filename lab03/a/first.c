#include<stdio.h>
#include<stdlib.h>

char* get_first() {
 char *name = malloc(10);
 puts("enter your first name:");
 gets(name);
 return name;
}

