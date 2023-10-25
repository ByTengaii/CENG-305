#include <sys/types.h>
#include <stdio.h> 
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main (void)
{
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];
    pid_t pid;

    int fd[2];

    if (pipe(fd) == -1)
    {
        fprintf(stderr, "\nPipe failed\n");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {// Fork failed
        fprintf(stderr, "\nFork failed\n");
    }
    else if (pid > 0)
    {// Parent process
        close(fd[READ_END]); // Close the read pipe
        write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
        close(fd[WRITE_END]);
    } 
    else
    { // Child process
        close(fd[WRITE_END]); // Close the write pipe
        read(fd[READ_END], read_msg, BUFFER_SIZE); // Reading from pipe's message that coming from PARENT
        printf("\n Child read from fd[0] is: %s \n", read_msg);
        close(fd[READ_END]);
    }
    
    return 0;
}