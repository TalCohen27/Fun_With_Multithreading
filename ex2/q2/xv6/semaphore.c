#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"

#define SEM_MAX_LEN	6

struct sem{
		struct spinlock sslock; // single semaphore lock
		int value;
		char *name;
		int ref;
	};

struct {
		struct spinlock gslock; //global semaphore lock
		struct sem sems[NSEM];
	} stable;

int sdalloc(struct sem *s);
int argsd(int n, int *psd, struct sem **ps);
int sys_sem_open(void); 
struct sem* semalloc(char * name, int create, int init);
int sys_sem_wait(void);
int sys_sem_trywait(void);
int sys_sem_signal(void);
int sys_sem_close(void);
 
int
argsd(int n, int *psd, struct sem **ps)
 {
	int sd;
	struct sem *s;

	if(argint(n, &sd) < 0)
		return -1;
	if(sd < 0 || sd >= NOSEM || (s=proc->osem[sd]) == 0)
		return -1;
	if(psd)
		*psd = sd;
	if(ps)
		*ps = s;
	return 0;
 }

 void stableLockInit(void)
 {
	initlock(&stable.gslock, "gslock");
 }

int sys_sem_open(void) //(char *name, int create, int init)
{
	char *name;
	int sd, init, create;
	struct sem *s;

	if(argstr(0, &name) < 0 || argint(1, &create) < 0 || argint(2, &init) < 0)
		return -1;
		
	if(strlen(name) > SEM_MAX_LEN || init < 0)
		return -1;
	
	if(((s = semalloc(name, create, init)) == 0 || (sd = sdalloc(s)) < 0))
		return -1;
	
	return sd;
}

// place given semaphore pointer in proc osem array
// and increment ref count
int
sdalloc(struct sem *s)
 {
	int sd;
	for(sd = 0; sd < NOSEM; sd++){
		if(proc-> osem[sd] == 0){
			proc-> osem[sd] = s;
			s->ref++;
			return sd;
		}
	}
	
	return -1;
 }
 
// look for an existing (same name, ref count >= 1) semaphore
// if not found and create is 1, create new semaphore with new->name = name
// and new->value = init. If success return pointer to new/existing semaphore
// otherwise return 0
 struct sem*
 semalloc(char * name, int create, int init)
 {
	struct sem *s = 0, *new = 0;
	
	acquire(&stable.gslock);
	for(s = stable.sems; s < stable.sems + NSEM; s++){
		if(s->ref >= 1 && strncmp(name, s->name, strlen(name)) == 0)
		{	
			release(&stable.gslock);
			return s;
		}
		else if(s->ref == 0)
			new = s;
	}
	
	if(new != 0 && create == 1)
	{	
		new->value = init;
		safestrcpy(new->name, name, strlen(name));
		initlock(&new->sslock, new->name);
		release(&stable.gslock);
		return new;
	}
	
	release(&stable.gslock);
	return 0;
 }
 
 // close semaphore by decrementing ref count
 // and nullifying the pointer in osem
 int sys_sem_close(void)
 {
	int sd;
	struct sem *s;

	if(argsd(0, &sd, &s) < 0) 
		return -1;
		
	if(sd >= 0 && sd < NOSEM && proc->osem[sd])
	{
		semclose(s);
		proc->osem[sd] = 0;
		return 0;
    }
		
	return -1;
}

// decrement smeaphore ref count	
void semclose(struct sem *s)
{

	acquire(&stable.gslock);
	if(s->ref < 1)
		panic("semclose");
	s->ref--;
	release(&stable.gslock);
}

 int sys_sem_wait(void)
 {
	int sd;
	struct sem *s;
	
	if(argsd(0, &sd, &s) < 0)
		return -1;
		
	acquire(&s->sslock);
	while(s->value -1 < 0)			// not possible, go to sleep
		sleep(&s->value, &s->sslock);
	s->value--;						//after value is positive, decrement it
	release(&s->sslock);
	return 0;
}

int sys_sem_trywait(void)
{
	int sd;
	struct sem *s;
	
	if(argsd(0, &sd, &s) < 0)
		return -1;
		
	acquire(&s->sslock);
		if(s->value -1 < 0)		//not possible, failure
		{
			release(&s->sslock);
			return -1;
		}
	s->value--;
	release(&s->sslock);
	return 0;			//success

}

int sys_sem_signal(void)
{
	int sd;
	struct sem *s;
	
	if(argsd(0, &sd, &s) < 0)
		return -1;
	acquire(&s->sslock);
	s->value++;
	wakeup(&s->value);
	release(&s->sslock);
	
	return 0;	
}

struct sem * semdup(struct sem * s)
{
	acquire(&stable.gslock);
	if(s->ref < 1)
		panic("semdup");
	s->ref++;
	release(&stable.gslock);
	return s;
}
