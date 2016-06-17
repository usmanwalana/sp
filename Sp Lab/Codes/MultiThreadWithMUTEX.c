#include <pthread.h>
#include <syscall.h>
#include <stdio.h>
#include <sys/types.h>

void *printA();
void *printB(void *);

	
char next='A';
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

int main(){

	pthread_t t1,t2;

	pthread_create(&t1,NULL,printA,NULL);
	pthread_create(&t2,NULL,printB,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

}

void *printA()
{    
	while(1){
pthread_mutex_lock(&lock);
if(next == 'A'){
	printf("A\n");
next='B';
}
pthread_mutex_unlock(&lock);
	}
}

void *printB(void *numB)
{
       while(1){
pthread_mutex_lock(&lock);
if(next == 'B'){
	printf("B\n");
next='A';
}
pthread_mutex_unlock(&lock);
	}
}
