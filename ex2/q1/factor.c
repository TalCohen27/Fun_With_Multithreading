#include "shared.h"

void printfPrimeFactors(int num);

// factor reads from the shared memory sp_array
// one number (semi-prime) at a time
// calculates its prime factors
// finally, prints the prime factors
// in the linux factor command format
int main()
{
	int num, sfd;
	void *base;
	sem_t *sem_sp_write, *sem_sp_read, *sem_sp_access;
	CyclicSpArray *spArr;

	printf("Ex#2, Q1, Tal Cohen, id 302529672\n");

	// opening psp shared memory
	sfd = shm_open(S_NAME, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG);
	if (sfd == -1) {
    printf("Shared memory failed: %s\n", strerror(errno));
    exit(1);
  }
 
 	// mapping shared memory
	base = mmap(NULL, sizeof(CyclicNumArray) + sizeof(CyclicSpArray), O_RDWR, MAP_SHARED, sfd, 0);
	spArr = base + sizeof(CyclicNumArray);

	// opening semaphores
	sem_sp_write = sem_open(SEM_SP_ARR_WRITE, O_CREAT, S_IRWXU, NO_SP_ARR); 
	sem_sp_read = sem_open(SEM_SP_ARR_READ, O_CREAT, S_IRWXU, SEM_READ_INIT);
	sem_sp_access = sem_open(SEM_SP_ARR_ACCESS, O_CREAT, S_IRWXU, SEM_ACCESS_INIT);

	while(1)
	{
		sem_wait(sem_sp_read);
		sem_wait(sem_sp_access);
		usleep(U_SLEEP);
		num = caRead(spArr->nums, spArr->size, &spArr->count, &spArr->start);
		sem_post(sem_sp_access);
		sem_post(sem_sp_write);
		printfPrimeFactors(num);
	}

	return 0;
}

void printfPrimeFactors(int num)
{

	int i;

	for(i = 2; i <= sqrt(num); i++){

		if(isPrime(i) && num % i == 0)
		{
			printf("%d: %d %d\n", num, i, num/i);
			break;
		}
	}

}