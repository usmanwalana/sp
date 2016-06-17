#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define MSGQ_KEY 123

#define MSG_TYPE1 1
#define MSG_TYPE2 5
#define MSG_TYPE3 10
#define MSG_TYPE4 20


typedef struct 
{
  long mtype;
  char msg[100];
} msgstruct;
