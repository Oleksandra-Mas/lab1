#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

ssize_t workWithBuffer(char *buffer, ssize_t size);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Enter input and output files, please\n");
        exit(1);
    }
    if (argc < 3)
    {
        printf("Enter output file, please\n");
        exit(1);
    }
    char *inputFile = argv[1];
    char *outputFile = argv[2];
    int fInput = open(inputFile, O_RDONLY);
    if (fInput == -1)
    {
        printf("Cannot open input file %s,\nHere is the error: %s\n", inputFile, strerror(errno));
        exit(1);
    }
    int fOutput = open(outputFile, O_CREAT | O_WRONLY, 0644);
    if (fOutput == -1)
    {
        printf("Cannot open output file %s,\nHere is the error: %s\n", outputFile, strerror(errno));
        exit(1);
    }
    char buffer[513];
    ssize_t bytesRead = 0;
    ssize_t changedBytes = 0;

    do
    {
        bytesRead = read(fInput, buffer, 512);
        changedBytes += workWithBuffer(buffer, bytesRead);
        write(fOutput, buffer, bytesRead);
    } while (bytesRead == 512);

    printf("Changed %ld bytes\n", changedBytes);
    close(fInput);
    close(fOutput);
    return 0;
}
ssize_t workWithBuffer(char *buffer, ssize_t size)
{
    ssize_t changedBytes = 0;
    for (ssize_t i = 0; i <= size; i++)
    {
        if (buffer[i] >= 'a' && buffer[i] <= 'z')
        {
            buffer[i] -= 32;
            changedBytes++;
        }
    }
    return changedBytes;
}