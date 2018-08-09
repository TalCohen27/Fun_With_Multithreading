#include "shared.h"

#define SEM_NUM_ARR_READ "/sem_num_arr_read"
#define SEM_NUM_ARR_WRITE "/sem_num_arr_write"
#define SEM_NUM_ARR_ACCESS "/sem_num_arr_access"

sem_t *sem_num_arr_read, *sem_num_arr_write, *sem_num_arr_access;
sem_t *sem_sp_arr_write, *sem_sp_arr_read, *sem_sp_arr_access;


CyclicNumArray *num_array;
CyclicSpArray *sp_array;

void do_son(int);
void do_parent();
int shmInit(void *);
void fillZeroes(void);
void open_all_sem(void);
void writeTwoToNumArray(int nums[], int size, int *count, int *start, int num1, int num2);
void readTwoFromNumArray(int *num1, int *num2);
void shmUnmapAndUnlink(void *shm, int sfd);
void writeOneToSpArray(int num);

int main()
{
	int pid, i, sfd, status;
	void *shmBase = NULL;

	printf("Ex#2, Q1, Tal Cohen, id 302529672\n");
	// open sems
	open_all_sem();
	sfd = shmInit(shmBase);

	for(i = 0; i < NO_SONS; i++){
		pid = fork();
		if (pid < 0)
		{			
			perror("Failed to fork a child process");
			exit(EXIT_FAILURE);
		}
		else if(pid == 0)
		{
			do_son(sfd);
			exit(0);
		}
	}

	do_parent();
	fillZeroes();
	for(i = 0; i < NO_SONS; i++)
	{
		printf("parent waiting (%d)\n", i);
		wait(&status);
	}

  shmUnmapAndUnlink(shmBase, sfd);

  return 0;

}

// parent reads numbers from stdin
// till EOF (ctrl + d)
// writes each pair into num_array
// then writes pairs of zeros into num_array
void do_parent()
{
	int num1, num2;

	printf("Please enter pairs of positive numbers\n");
	do
	{
	    scanf("%d%d", &num1, &num2);
		if(!feof(stdin)) 
		   writeTwoToNumArray(num_array->nums, num_array->size, &num_array->count, &num_array->start, num1, num2);
	}while(!feof(stdin));
}

// son reads pairs of numbers from num_array
// then calculates nearest prime for each of them
// multiplies the two primes
// finally, writes the resulting semi-prime into sp_array
void do_son(int sfd)
{
	int num1, num2, sp;
	
	do
	{
		readTwoFromNumArray(&num1, &num2);
		if(num1 != 0)
		{
			num1 = calcNearestPrime(num1);
			num2 = calcNearestPrime(num2);
			sp = num1*num2;
			writeOneToSpArray(sp);
		}

	}while(num1 != 0);
}

int calcNearestPrime(int num)
{
	int found = 0;

	while(!found)
		found = isPrime(num++);

	return num - 1;
}

int shmInit(void *shmBase)
{
	// opening shared memory
	int sfd = shm_open(S_NAME, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG);
	if (sfd == -1) {
    printf("Shared memory failed: %s\n", strerror(errno));
    exit(1);
  	}

  	// resizing to fit
	ftruncate(sfd,  sizeof(CyclicNumArray) + sizeof(CyclicSpArray));
	// mapping
	shmBase = mmap(NULL,  sizeof(CyclicNumArray) + sizeof(CyclicSpArray), O_RDWR, MAP_SHARED, sfd, 0);

	if (shmBase == MAP_FAILED) {
    printf("prod: Map failed: %s\n", strerror(errno));
 
    exit(1);
  }
  	num_array = shmBase;
	caInit(&num_array->size, NO_NUM_ARR, &num_array->start, &num_array->count);
	sp_array = shmBase + sizeof(CyclicNumArray);
	caInit(&sp_array->size, NO_SP_ARR, &sp_array->start, &sp_array->count);

	return sfd;
}

// free shared memory
void shmUnmapAndUnlink(void *shm, int sfd)
{
	
    if(munmap(shm, sizeof(CyclicNumArray) + sizeof(CyclicSpArray)) == -1) {
    printf("prod: Unmap failed: %s\n", strerror(errno));
    exit(1);
	}

	if (close(sfd) == -1) {
    printf("prod: Close failed: %s\n", strerror(errno));
    exit(1);
  }

  if (shm_unlink(S_NAME) == -1) {
   printf("cons: Error removing %s: %s\n", S_NAME, strerror(errno));
     exit(1);
   }
}

void fillZeroes()
{
	int i;
	for(i = 0; i < NO_SONS; i++)
		writeTwoToNumArray(num_array->nums, num_array->size, &num_array->count, &num_array->start, 0, 0);
}

void writeTwoToNumArray(int nums[], int size, int *count, int *start, int num1, int num2)
{
  
   	sem_wait(sem_num_arr_write);
	sem_wait(sem_num_arr_access);
	usleep(U_SLEEP);
	caWrite(nums, size, count, start, num1);
	caWrite(nums, size, count, start, num2);
	sem_post(sem_num_arr_access);
	sem_post(sem_num_arr_read);	
}


void readTwoFromNumArray(int *num1, int *num2)
{
	sem_wait(sem_num_arr_read);
	sem_wait(sem_num_arr_access);
	usleep(U_SLEEP);
	*num1 = caRead(num_array->nums, num_array->size, &num_array->count, &num_array->start);
	*num2 = caRead(num_array->nums, num_array->size, &num_array->count, &num_array->start);
	sem_post(sem_num_arr_access);
	sem_post(sem_num_arr_write);
}

void writeOneToSpArray(int num)
{
	sem_wait(sem_sp_arr_write);
	sem_wait(sem_sp_arr_access);
	usleep(U_SLEEP);
	caWrite(sp_array->nums, sp_array->size, &sp_array->count, &sp_array->start, num);
	sem_post(sem_sp_arr_access);
	sem_post(sem_sp_arr_read);
}


void open_all_sem(void)
{
	//free
	if (sem_unlink(SEM_NUM_ARR_WRITE)==0)
		fprintf(stderr, "successul unlink of /sem_num_arr_write\n");
	sem_num_arr_write = sem_open(SEM_NUM_ARR_WRITE, O_CREAT, S_IRWXU, NO_NUM_ARR/2); 
	if (sem_num_arr_write == SEM_FAILED)
	{
		perror("failed to open semaphore /sem_num_arr_write\n");
		exit(EXIT_FAILURE);
	}
	//count
	if (sem_unlink(SEM_NUM_ARR_READ)==0)
		fprintf(stderr, "successul unlink of /sem_num_arr_read\n");
	sem_num_arr_read = sem_open(SEM_NUM_ARR_READ, O_CREAT, S_IRWXU, SEM_READ_INIT); 
	if (sem_num_arr_read == SEM_FAILED)
	{
		perror("failed to open semaphore /sem_num_arr_read\n");
		exit(EXIT_FAILURE);
	}	
	
	//access
	if (sem_unlink(SEM_NUM_ARR_ACCESS)==0)
		fprintf(stderr, "successul unlink of /sem_num_arr_access\n");
	sem_num_arr_access = sem_open(SEM_NUM_ARR_ACCESS, O_CREAT, S_IRWXU, SEM_ACCESS_INIT); 
	if (sem_num_arr_access == SEM_FAILED)
	{
		perror("failed to open semaphore /sem_num_arr_access\n");
		exit(EXIT_FAILURE);
	}	


	if (sem_unlink(SEM_SP_ARR_ACCESS)==0)
		fprintf(stderr, "successul unlink of /sem_sp_arr_access\n");
	sem_sp_arr_access = sem_open(SEM_SP_ARR_ACCESS, O_CREAT, S_IRWXU, SEM_ACCESS_INIT); 
	if (sem_sp_arr_access == SEM_FAILED)
	{
		perror("failed to open semaphore /sem_sp_arr_access\n");
		exit(EXIT_FAILURE);
	}

	if (sem_unlink(SEM_SP_ARR_WRITE)==0)
		fprintf(stderr, "successul unlink of /sem_sp_arr_write\n");
	sem_sp_arr_write = sem_open(SEM_SP_ARR_WRITE, O_CREAT, S_IRWXU, NO_SP_ARR); 
	if (sem_sp_arr_write == SEM_FAILED)
	{
		perror("failed to open semaphore /sem_sp_arr_write\n");
		exit(EXIT_FAILURE);
	}

	if (sem_unlink(SEM_SP_ARR_READ)==0)
		fprintf(stderr, "successul unlink of /sem_sp_arr_read\n");
	sem_sp_arr_read = sem_open(SEM_SP_ARR_READ, O_CREAT, S_IRWXU, SEM_READ_INIT); 
	if (sem_sp_arr_read == SEM_FAILED)
	{
		perror("failed to open semaphore /sem_sp_arr_read\n");
		exit(EXIT_FAILURE);
	}	
}
