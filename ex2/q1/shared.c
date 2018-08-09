
#include "shared.h"

void caInit(int *size, int newSize, int *start, int *count) {

     *size = newSize;
     *start = 0;
     *count = 0;
 }

void caWrite(int nums[], int size, int *count, int *start, int num) {

	int end = (*start + *count) % size;
	nums[end] = num;
    if(*count == size)
        *start = (*start + 1) % size; /* full, overwrite */
    else
         (*count)++;
}

int caRead(int nums[], int size, int *count, int *start) {
    int num;  
    
    num = nums[*start];
    *start = (*start + 1) % size;
    (*count)--;

    return num;
}

int isPrime(int num)
{
	int i;
	
	for(i = 2; i <= sqrt(num) || num == 1; i++)
		if(num % i == 0 || num == 1)
			return 0;
	return 1;
}

