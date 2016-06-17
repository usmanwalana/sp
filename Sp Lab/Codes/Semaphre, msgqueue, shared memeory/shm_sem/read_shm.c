#include "my_ipc.h"

int main()
{
  int sem_id;
  int shm_id;
  char *shared_memory;
  shm_id = shmget (SHM_KEY, shared_segment_size, 0600 );
  shared_memory = (char*) shmat (shm_id, 0, 0);
  if ( (sem_id =  semget (SEM_KEY, 1, 0600 )) == -1 )
  {
    perror ("Unable to get hold of the semaphore ");
    exit(5);
  }
  binary_semaphore_wait (sem_id);
  printf ("Message in shared memory was %s \n", shared_memory );
}

/* Wait on a binary semaphore.  Block until the semaphore value is
   positive, then decrement it by one.  */

binary_semaphore_wait (int semid)
{
  union semun argument;
  struct sembuf operations[1];
  
  /* Use the first (and only) semaphore.  */
  operations[0].sem_num = 0;

  /* Decrement by 1.  */
  operations[0].sem_op = -1;
  operations[0].sem_flg = 0;

  printf ("The value of semaphore before semop is %d \n", 
	  semctl ( semid, 0, GETVAL, argument ));
  if ( semop (semid, operations, 1) == -1 )
  {
    perror ("Unable to perform required operation");
    exit(0);
  }
  printf ("The value of semaphore after semop is %d \n", 
	  semctl ( semid, 0, GETVAL, argument ));
}

