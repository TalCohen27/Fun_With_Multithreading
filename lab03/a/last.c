#include<stdio.h>
#include<stdlib.h>

char* get_last() {
 char *name = malloc(10);
 puts("enter your Last name:");
 gets(name);
 return name;
}

