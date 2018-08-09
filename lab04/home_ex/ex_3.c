
#include <stdio.h>
#include <stdlib.h>

#define A_TYPE_FACTOR 0
#define B_TYPE_FACTOR 1
#define C_TYPE_FACTOR 2

#define NELEM(x) (sizeof(x)/sizeof((x)[0]))

float factor1 = 1.2;
int factor2 = 15;

int factorA(int grade, void *factor);
int factorB(int grade, void *factor);
int factorC(int grade, void *factor);

static struct Student
{
   char * name;
   int grade;
   int final_grade;
   void *factor;	
   int factor_type;		

} student[] = {

	{"avi", 70, 0, &factor1, A_TYPE_FACTOR},
	{"beni", 60, 0, &factor2, B_TYPE_FACTOR},
	{"cobi", 80, 0, &factor1, C_TYPE_FACTOR},
	{"tzvi", 80, 0, &factor1, A_TYPE_FACTOR},
	{"Tal Cohen", 100, 0, &factor1, A_TYPE_FACTOR },
};


static int (*factors[])(int, void *) = {
	
	[A_TYPE_FACTOR] factorA,
	[B_TYPE_FACTOR] factorB,
	[C_TYPE_FACTOR] factorC,

};

int factorA(int grade, void *factor)
{ 

   return (*(float *)factor)*grade;
}

int factorB(int grade, void *factor)
{
	return grade + *((int *)factor);

}

int factorC(int grade, void *factor)
{
     return *((float *)factor)*grade - 5;

}

int main()
{
	int k;
	int newGrade;
	struct Student currStudent;
	int (*factorMethod)(int, void *);
	for(k = 0; k < NELEM(student); k++)
		{
			
			currStudent = student[k];
			factorMethod = factors[currStudent.factor_type];
			newGrade = factorMethod(currStudent.grade, currStudent.factor);
			printf("name: %s grade: %d, Factor-type: %d grade after factor: %d\n", currStudent.name, currStudent.grade, currStudent.factor_type, newGrade);
		}
return 0;

}