#include<stdio.h>

char* get_first();
char* get_last();
void greet(char *);

int main () {
 char *first, *last;
 first = get_first();
 last = get_last();
 printf("hello %s %s!!\n", first, last);
 return 0;
}
 

 