#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>

int main()
{
    int fd;
    char *fifoPath = "/tmp/myfifo";
    char arr1[80], arr2[80];
    mkfifo(fifoPath, 0666);    

    while (1)
    {
        fd = open(fifoPath, O_RDONLY); // Open the fifo
        read(fd, arr1, 80); // read from fifo to arr1
        printf("User1: %s\n", arr1);
        close(fd);
        fd = open(fifoPath, O_WRONLY);
        printf("User2:");
        fgets(arr2, 80, stdin);
        write(fd, arr2, strlen(arr2)+1);
        close(fd);
    }
    
}