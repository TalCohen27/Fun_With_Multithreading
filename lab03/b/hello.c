#include<stdio.h>
#include "hello.h"
#include "color.h"

int main () {
 char *first, *last, *color;
 char greeting[50];
 first = get_first();
 last = get_last();
 color = get_color();
 sprintf(greeting, "Hello %s %s!!\n", first, last);
 print_color(color, greeting);
 printf("bye!\n");

 return 0;
}
 

 
