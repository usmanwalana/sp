#include "my_ipc.h"

int main()
{
  int sem_id;
  if ( (sem_id =  semget (SEM_KEY, 
			  1, IPC_CREAT | IPC_EXCL | 0600 )) == -1 )
  {
    perror ("Unable to create semaphore");
    exit(5);
  }
  binary_semaphore_initialize (sem_id);
}


int binary_semaphore_initialize (int semid)
{
  union semun argument;
  unsigned short values[1];
  values[0] = 1;
  argument.array = values;
  return semctl (semid, 0, SETALL, argument);
}
