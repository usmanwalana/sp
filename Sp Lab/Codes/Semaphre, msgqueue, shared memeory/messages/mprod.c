#include "msg_header.h"

extern int errno;

int main()
{
  int mq_id, msg_size;
  struct msqid_ds msgq_ds;
  msgstruct mymessage;
  
  mq_id = msgget ( MSGQ_KEY, IPC_CREAT | 0600 );
  if ( mq_id == -1)
  {
    printf ("msgget Error : %s \n", strerror(errno));
    exit(1);
  }
  // get the info about this message queue
  if ( (msgctl ( mq_id, IPC_STAT, &msgq_ds ))  == -1 )
  {
    printf ("msgctl Error : %s \n", strerror(errno));
    exit(1);
  }
  printf ("Enter message type : ");
  scanf ("%ld", &mymessage.mtype );
  getchar();
  printf ("Enter message : ");
  gets(mymessage.msg );
  msg_size = strlen (mymessage.msg);
  
  if ( msgsnd ( mq_id, &mymessage, msg_size, 0 )  == -1 )
  {
    printf ("msgsnd Error : %s \n", strerror(errno));
    exit(1);
  }
  
}

