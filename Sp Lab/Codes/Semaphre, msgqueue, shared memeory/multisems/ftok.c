#include "my_ipc.h"

int main( int argc, char *argv[])
{
  int sem_id, proj_id;
  key_t mykey;

  if ( argc != 3 )
  {
	printf ("Usage : %s file_name projectID\n", argv[0]);
	return 1;
  }
  proj_id = atoi(argv[2]);
  mykey = ftok ( argv[1], proj_id );
  printf ("The key returned by ftok is %d\n",mykey);
  if ( (sem_id =  semget (mykey,
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
