/* Copyright (c) 2005 Russ Cox, MIT; see COPYRIGHT */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <task.h>
#include <sys/time.h>

int quiet;
int goal;
int buffer;
uint64_t start_time = 0;
uint64_t end_time = 0;

uint64_t GetCurrentMs() {
        struct timeval time;
        gettimeofday(&time, NULL);
        //return time.tv_sec * 1000 + time.tv_usec / 1000;
        return time.tv_sec * 1000ul + time.tv_usec / 1000;
    }

    uint64_t GetCurrentUs() {
        struct timeval time;
        gettimeofday(&time, NULL);
        return time.tv_sec * 1000 * 1000ul + time.tv_usec;
    }

void
primetask(void *arg)
{
	//Channel *c, *nc;
	int c, p, i;
	c = arg;

	//p = chanrecvul(c);
	//if(p > goal)
	//	taskexitall(0);
	//if(!quiet)
	//	printf("%d\n", p);
	//nc = chancreate(sizeof(unsigned long), buffer);
	//taskcreate(primetask, nc, 32768);
	//for(;;){
	//	i = chanrecvul(c);
	//	if(i%p)
	//		chansendul(nc, i);
	//}
	while(c--)
		taskyield();
	end_time = GetCurrentMs();	
	printf("end_time: %ld\n", end_time);
	printf("elapse time: %ld\n", end_time - start_time);
}

void
taskmain(int argc, char **argv)
{
	int i;
	Channel *c;

	if(argc>1)
		goal = atoi(argv[1]);
	else
		goal = 100;
	printf("goal=%d\n", goal);

	c = chancreate(sizeof(unsigned long), buffer);
	taskcreate(primetask, 1000000, 32768);
	start_time = GetCurrentMs();	
	printf("start_time: %ld\n", start_time);

}

void*
emalloc(unsigned long n)
{
	return calloc(n ,1);
}

long
lrand(void)
{
	return rand();
}
