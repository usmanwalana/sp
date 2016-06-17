#include "my_ipc.h"

int main()
{
  int sem_id, user_type, plain, choc;
  char *shared_memory;
  if ( (sem_id =  semget (SEM_KEY, 1, 0600 )) == -1 )
  {
    perror ("Unable to get hold of the semaphore ");
    exit(5);
  }
  printf ("Enter 0 if you are a producer or 1 if you are a consumer : ");
  scanf ("%d", &user_type );
  if ( user_type )
  {
    printf ("How many plain doughnuts you want to consume : ");
    scanf ("%d", &plain );
    printf ("How many chocolate doughnuts you want to consume : ");
    scanf ("%d", &choc );
    semaphore_wait (sem_id, plain,  choc);
    printf ("Process %d done eating doughnuts\n", getpid());
  }
  else
  {
    printf ("How many plain doughnuts you want to produce : ");
    scanf ("%d", &plain );
    printf ("How many chocolate doughnuts you want to produce : ");
    scanf ("%d", &choc );
    semaphore_post (sem_id, plain,  choc);
    printf ("Process %d done baking doughnuts\n", getpid());
  }
}


semaphore_wait (int semid, int  p, int c)
{
  union semun argument;
  unsigned short values[3];
  argument.array = values;
  struct sembuf operations[2];
  /* PLAIN      doughnut */
  operations[PLAIN].sem_num = 0;
  operations[PLAIN].sem_op = -p;
  operations[PLAIN].sem_flg = 0;
  /* CHOC   doughnuts */
  operations[CHOC].sem_num = 1;
  operations[CHOC].sem_op = -c;
  operations[CHOC].sem_flg = 0;
  /* Permit undo'ing.  */
  //  operations[0].sem_flg = SEM_UNDO;
  if (semctl ( semid, 0, GETALL, argument ) == -1)
  {
	perror ("semclt:");
	exit(0);
  }
  printf ("There are %d plain dougnuts before semop \n", argument.array[0]);
//	  semctl ( semid, 0, GETVAL, argument ));
  printf ("There are %d chocolate dougnuts before semop \n", argument.array[1]);
//	  semctl ( semid, 1, GETVAL, argument )); 
  fflush (stdout);
  if ( semop (semid, operations, 2) == -1 )
  {
    perror ("Unable to perform required operation");
    exit(0);
  }
  printf ("There are %d plain dougnuts after semop \n", 
	  semctl ( semid, 0, GETVAL, argument ));
  printf ("There are %d chocolate dougnuts after semop \n",
	  semctl ( semid, 1, GETVAL, argument )); 
  fflush (stdout);
}

semaphore_post (int semid, int  p, int c)
{
  union semun argument;
  struct sembuf operations[2];
  /* PLAIN      doughnut */
  operations[PLAIN].sem_num = 0;
  operations[PLAIN].sem_op = p;
  operations[PLAIN].sem_flg = 0;
  /* CHOC   doughnuts */
  operations[CHOC].sem_num = 1;
  operations[CHOC].sem_op = c;
  operations[CHOC].sem_flg = 0;
  /* Permit undo'ing.  */
  printf ("There are %d plain dougnuts before semop \n", 
	  semctl ( semid, 0, GETVAL, argument ));
  printf ("There are %d chocolate dougnuts before semop \n",
	  semctl ( semid, 1, GETVAL, argument )); 
  fflush (stdout);
  if ( semop (semid, operations, 2) == -1 )
  {
    perror ("Unable to perform required operation");
    exit(0);
  }
  printf ("There are %d plain dougnuts after semop \n", 
	  semctl ( semid, 0, GETVAL, argument ));
  printf ("There are %d chocolate dougnuts after semop \n",
	  semctl ( semid, 1, GETVAL, argument )); 
  fflush (stdout);
}

