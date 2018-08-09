#include "types.h"
#include "stat.h"
#include "user.h"


static int buf[10000];
int
main(int argc, char *argv[])
{

	int i;
	
	//buf[0] = 0;
	for(i = 0; i < 10000; i++)
		buf[i] = 0;
	exit();
}