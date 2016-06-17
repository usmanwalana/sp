#include "msg_header.h"

extern int errno;

int main()
{
  int mq_id, msg_size = 100;
  long mtype;
  struct msqid_ds msgq_ds;
  msgstruct mymessage;
  
  mq_id = msgget ( MSGQ_KEY, 0600 );
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
  scanf ("%ld", &mtype );
  memset ( &mymessage, '\0', sizeof ( msgstruct ));
  if ( msgrcv ( mq_id, &mymessage, msg_size, mtype,  0 )  == -1 )
  {
    printf ("msgrcv Error : %s \n", strerror(errno));
    exit(1);
  }
  printf ("Message read from msg queue is %s \n", mymessage.msg );
  
  if ( msgctl ( mq_id, IPC_STAT, &msgq_ds )  == -1 )
  {
    printf ("msgctl Error : %s \n", strerror(errno));
    exit(1);
  } 
  printf ("The current state of the message is as follows : \n");
  printf ("PID of the last proc that wrote a message : %d \n", msgq_ds.msg_lspid );
  printf ("PID of the last proc that read a message : %d \n", msgq_ds.msg_lrpid );
  printf ("Current number of bytes on queue  : %d \n", msgq_ds.msg_cbytes );
  printf ("Current number of messages on queue : %d \n", msgq_ds.msg_qnum );
  printf ("Max number of bytes allowed  on queue : %d \n", msgq_ds.msg_qbytes );
  printf ("Owner's effective user id : %d \n", msgq_ds.msg_perm.uid );
  printf ("Owner's effective group id : %d \n", msgq_ds.msg_perm.gid );
}
/*
  printf ("Time last message was sent : %s \n", ctime(&msgq_ds.msg_stime) );
  printf ("Time last message was received : %s \n", ctime(&msgq_ds.msg_rtime) );
  printf ("Time when queue was last changed : %s \n", ctime(&msgq_ds.msg_ctime) );
*/
