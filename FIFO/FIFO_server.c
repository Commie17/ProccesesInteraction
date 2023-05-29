#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_BUFFER "Buffer_FIFO"
int main() 
{
    int fd;
    char receivedString[10];
    int read_bytes;
   
    /* Create the FIFO if it does not exist */
    mkfifo(FIFO_BUFFER,O_CREAT|O_EXCL|O_RDONLY);
    fd = open(FIFO_BUFFER, O_RDONLY);

    while(1) 
    {
        read_bytes = read(fd, receivedString, sizeof(receivedString));
        receivedString[read_bytes]='\0';
        printf("Received number: \"%s\" \n",receivedString);

        if(receivedString[0]!='0')
        {
            printf("Received number multiplied by 10: \"%s0\" \n", receivedString);
        }
        else
        {
            close(fd);
            break;
        }
    }
    return 0;
}