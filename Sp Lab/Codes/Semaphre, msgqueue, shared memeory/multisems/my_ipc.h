#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>


#define SHM_KEY 123
#define SEM_KEY 456
#define PLAIN 0
#define CHOC 1

const int shared_segment_size = 0x6400;

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
  struct seminfo *__buf;
}arg;


