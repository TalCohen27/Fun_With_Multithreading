#include "types.h"
#include "user.h"
#include "stat.h"

#define NUM_CHILDREN 1

// Thanks to the semaphore, the only possible output is:

// First Father printf
// First Son printf
// Second Father printf
// Second Son printf

// without the semaphores, the order could be any combination!
int main()
{
	int i, pid, sd1, sd2, sd3;
	printf(1, "Ex#2, Q2, Tal Cohen, id 302529672\n");
	sd1 = sem_open("son", 1, 0);
	sd2 = sem_open("parent", 1, 1);
	sd3 = sem_open("non-create", 0, 0);
	printf(1, "ret value for non-create, non existing sem is: %d\n", sd3); // should be -1
	sd3 = sem_open("create", 1, 5);
	for(i = 0; i < NUM_CHILDREN; i++)
	{
		pid = fork();
		if(pid == 0)
	    {
			// son part
		    sem_wait(sd1);
	    	printf(1, "First Son printf\n");
			sleep(3);
			sem_signal(sd2);
			sem_wait(sd1);
			printf(1, "Second Son printf\n");
			
			sem_close(sd1);
			sem_close(sd2);
			sem_close(sd3);
	    	exit();
		}
	}
	
	// rest of father part
	sem_wait(sd2);
	printf(1, "First Father printf\n");
	sem_signal(sd1);
	sem_wait(sd2);
	printf(1, "Second Father printf\n");
	sem_signal(sd1);

	for(i = 0; i < NUM_CHILDREN; i++)
		wait();
	
	printf(1, "Return value of sem_trywait in case value is 0: %d\n", sem_trywait(sd1));	// should be -1
	printf(1, "Return value of sem_trywait in case value is positive: %d\n", sem_trywait(sd3)); // should be 0
	sem_close(sd1);
	sem_close(sd2);	
	sem_close(sd3);
	exit();
}