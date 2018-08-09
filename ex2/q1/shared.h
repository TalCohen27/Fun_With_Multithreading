
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>  
#include <sys/wait.h>
#include <semaphore.h>
#include <math.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

#define S_NAME "/arrays"

#define NO_SONS 3 // number of children process in psp program
#define NO_NUM_ARR 8 // number of entries in num_array.
// of course, number of pairs is half of that
#define NO_SP_ARR 3 // number of entries in sp_array.
#define U_SLEEP 200000 // micro-sec of delay.
#define SEM_SP_ARR_WRITE "/sem_sp_arr_write"	// semaphore names
#define SEM_SP_ARR_READ "/sem_sp_arr_read"
#define SEM_SP_ARR_ACCESS "/sem_sp_arr_access"
#define SEM_READ_INIT 0
#define SEM_ACCESS_INIT 1


typedef struct CyclicSpArray{
    int   size;   
    int   start;  
    int   count;    
    int   nums[NO_SP_ARR];              
}CyclicSpArray;

 typedef struct CyclicNumArray{
    int   size;   
    int   start;  
    int   count;    
    int   nums[NO_NUM_ARR];              
}CyclicNumArray;


void caInit(int *size, int newSize, int *start, int *count);
void waitAndWrite(int nums[], int size, int *count, int *start, int num);
void caWrite(int nums[], int size, int *count, int *start, int num);
int caRead(int nums[], int size, int *count, int *start);
void open_all_sem(void);
int calcNearestPrime(int num);
int isPrime(int num);




