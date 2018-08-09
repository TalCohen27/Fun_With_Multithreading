#include "types.h"
#include "user.h"
#include "stat.h"

#define NUM_CHILDREN 3

int main()
{
	int i, pid, status;
	
	printf(1, "Ex#1, Q3, Tal Cohen, id 302529672\n");
	for(i = 0; i < NUM_CHILDREN; i++)
	{
		pid = fork();
		if(pid == 0)
	    {
	    	printf(1, "my pid is %d going to exit(%d)\n", getpid(), i + 1);
	    	exit2(i + 1);
		}
	}
	
	  for(i = 0; i < NUM_CHILDREN; i++)
	  {
			pid = wait2(&status);
			printf(1, "son %d exited with status %d\n", pid, status);
	  }
	  
	  exit();
}