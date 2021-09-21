#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Enter identifier, please\n");
        exit(1);
    }
    char *identifier = argv[1];
    struct pollfd fds[1];
    int retval, length;
    char buffer[1024];

    while (1)
    {
        fds[0].fd = STDIN_FILENO;
        fds[0].events = POLLIN;
        retval = poll(fds, 1, 5000);
        if (retval == -1)
        {
            printf("%s, Here is the error at select, %s", identifier, strerror(errno));
            exit(EXIT_FAILURE);
        }
        else if (retval)
        {
            ssize_t readBytes=read(STDIN_FILENO, buffer, 1024);
            length = readBytes-1;
            if (buffer[length] == '\n')
                buffer[length] = '\0';
            printf("%s: '%s'\n", identifier, buffer);
        }
        else
        {
            printf("%s: No data was entered in 5 seconds\n", identifier);
        }
    }
    return 0;
}