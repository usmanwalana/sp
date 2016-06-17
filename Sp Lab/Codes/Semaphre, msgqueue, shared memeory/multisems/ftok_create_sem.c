#include "my_ipc.h"

int main( int argc, char *argv[])
{
  int sem_id, proj_id;
  key_t my_sem_key;
  proj_id = atoi(argv[1]);
  my_sem_key = ftok("/etc/passwd", proj_id );
  if ( (sem_id =  semget (my_sem_key,
			  2, IPC_CREAT | IPC_EXCL | 0600 )) == -1 )
  {
    perror ("Unable to create semaphore");
    exit(5);
  }
  printf ("sem_id is %d\n", sem_id );
  semaphore_initialize (sem_id);
}


int semaphore_initialize (int semid)
{
  union semun argument;
  unsigned short values[2];
  values[PLAIN] = 0;
  values[CHOC] = 0;
  argument.array = values;
  return semctl (semid, 0, SETALL, argument);
}
