#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Enter identifier, please\n");
        exit(1);
    }
    char *identifier = argv[1];

    fd_set rfds;
    struct timeval tv;
    int retval; 
    char buffer[1024];

    while(1) {
        FD_ZERO(&rfds);
        FD_SET(STDIN_FILENO, &rfds);
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        
        retval = select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tv);
        if (retval == -1)
        {
            printf("%s, here is the error at select: %s", identifier, strerror(errno));
            exit(EXIT_FAILURE);
        }
        else if (retval)
        {
            if (FD_ISSET(STDIN_FILENO, &rfds)) {
                if (fgets(buffer,sizeof(buffer), stdin)) 
                    printf("%s: %s\n",identifier ,buffer);
                else
                    printf("Here is the error: %s\n", strerror(errno));
                    
            }
        }
        else
        {
            printf("No data was entered in 5 seconds\n");
        }
    }

    return 0;
}