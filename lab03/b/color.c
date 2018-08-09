#include<stdio.h>
#include<stdlib.h>

#include "color.h"

char* get_color() {
	char *color = malloc(10);
	int col;
	puts("enter number for color:\n \
	1 - red\n    \
	2 - green\n  \
	3 - yellow\n \
	4 (or any other) - blue");
	scanf("%i1", &col);
	
	switch(col)
	{
	case 1:  color=RED;    break;
	case 2:  color=GREEN;  break;
	case 3:  color=YELLOW; break;
	default: color=BLUE;   break;
	}
	return color;
}

void print_color(char* color, char* str)
{
	char tmpStr[60];
	sprintf(tmpStr,"%s%s%s",color,str,NO_COLOR);
	printf(tmpStr);
}
