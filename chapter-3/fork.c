#include <sys/types.h>
#include <stdio.h> 
#include <unistd.h>

int main()
{
    pid_t pid;

    printf("Process start \n");
    pid = fork();// Fork a child process

    if (pid < 0) // Error occured
    {
        fprintf(stderr, "Fork Failed\n");
    }
    else if ( pid == 0)
    {
        printf("Child Process\n");
        abort();
        printf("\nChild process after abort \n");
    }
    else //Parent process 
    {
        wait(NULL);
        printf("Child complete\n");   
    }
    printf("Process DONE\n");
}