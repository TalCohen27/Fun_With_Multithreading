#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
	char src1[] = "Tal Cohen id: 302529672";
	char src2[] = "some-other-string";
	char *dest = (char *)malloc(strlen(src1) + strlen(src2));
	asm volatile("rep movsb;" : : "S" (src1), "D" (dest), "c" (strlen(src1)));
	asm volatile("rep movsb;" : : "S" (src2), "D" (dest + strlen(src1)), "c" (strlen(src2)));
	printf("Before...\nsrc1 is: %s \nsrc2 is: %s \n", src1, src2);
	printf("After...(destination string)\n%s", dest);
	free(dest);
	
	return 0;
}
