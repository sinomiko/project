
#include	<sys/types.h>
#include	<sys/ipc.h>
#include	<sys/sem.h>
#include	<sched.h>
#include	<stdio.h>
#include	<errno.h>

#include "simp_sem.h"
#include "diners.h"
/*
 * Taken from "Operating Systems - Design and Implementation" by Tanenbaum
 * Section 2.3, page 91, Figure 2-10
 */
#define LEFT 		(i + N - 1) % N	/* i's left neighbor */
#define RIGHT 		(i + 1) % N	/* i's right neighbor */
#define THINKING	0		/* philosopher states */
#define HUNGRY		1
#define EATING		2

int state[N];
semaphore s[N];
semaphore mutex;


void take_forks (int);
void put_forks (int);
void test (int);

void think (int);
void eat (int);

void philosopher (void* i)
{
	int *phil = (int*)i;
	int awhile = 5;

	while (awhile--)
	{
		think(*phil);
		take_forks(*phil);
		eat(*phil);
		put_forks (*phil);
	}
}

void
take_forks (int i)
{
	sem_wait (mutex);
	state[i] = HUNGRY;
	test(i);
	sem_signal (mutex);
	sem_wait (s[i]);
}

void
put_forks (int i)
{
	sem_wait (mutex);
	state[i] = THINKING;
	test(LEFT);
	test(RIGHT);
	sem_signal (mutex);
}

void
test (int i)
{
	if (state[i] == HUNGRY &&
		state[LEFT] != EATING &&
		state[RIGHT] != EATING)
	{
		state[i] = EATING;
		sem_signal (s[i]);
	}
}

void think (int i)
{
	printf ("Philosopher %d thinking\n", i);
	sleep (2);
	printf ("Philosopher %d done thinking\n", i);
}

void eat (int i)
{
	printf ("Philosopher %d eating (%d, %d)\n", i, state[LEFT], state[RIGHT]);
	sleep (1);
	printf ("Philosopher %d done eating\n", i);
}
