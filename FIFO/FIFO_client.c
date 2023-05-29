#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "Buffer_FIFO"
int main() {

    int k;
    int fd;
    int end_process;
    int stringlen;
    char readbuf[8];
    char end_str[2];

    printf("FIFO_CLIENT: Send messages, to end enter \"0\"\n");
    fd = open(FIFO_FILE, O_CREAT|O_WRONLY);
    strcpy(end_str, "0");
   
    while (1) {
        printf("Enter number: ");
        fgets(readbuf, sizeof(readbuf), stdin);

        stringlen = strlen(readbuf);
        readbuf[stringlen - 1] = '\0';

        end_process = strcmp(readbuf, end_str);
      
        if (end_process != 0) {
            write(fd, readbuf, strlen(readbuf));
            printf("Sent number: \"%s\" \n", readbuf);
        } else {
            write(fd, readbuf, strlen(readbuf));
            printf("Sent number: \"%s\" \n", readbuf);
            close(fd);
            break;
        }
    }
    return 0;
}