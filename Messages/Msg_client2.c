#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PERMS 0666
struct message {
   long mtype;
   char mtext[200];
};

int main(void) 
{
    struct message buf;
    int msqid;
    int toend;
    key_t key;
   
    if ((key = ftok("msgq.txt", 'B')) == -1) 
    {
        perror("ftok");
        exit(1);
    }
   
    if ((msqid = msgget(key, PERMS)) == -1) 
    { 
        perror("msgget");
        exit(1);
    }
    printf("message queue: ready to receive messages.\n");
   
    for(;;) 
    { 
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 10, 0) == -1) 
        {
            perror("msgrcv");
            exit(1);
        }
        printf("recvd: \"%s\"\n", buf.mtext);

        if (buf.mtext=="end")
            break;
    }
    printf("message queue: done receiving messages.\n");
    system("rm msgq.txt");
    return 0;
}