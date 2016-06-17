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
  sprintf (shared_memory, "Hello world from process # %d ", getpid());
  binary_semaphore_post (sem_id);
}

/* Post to a binary semaphore: increment its value by one.  This
   returns immediately.  */

int binary_semaphore_post (int semid)
{
  struct sembuf operations[1];
  /* Use the first (and only) semaphore.  */
  operations[0].sem_num = 0;
  /* Increment by 1.  */
  operations[0].sem_op = 1;
  
  return semop (semid, operations, 1);
}
