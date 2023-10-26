#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>

int main()
{
    int fd;
    char *fifoPath = "/tmp/myfifo"; // FIFO file path
    char arr1[80], arr2[80];

    mkfifo(fifoPath, 0666);

    while(1)
    {
        fd = open(fifoPath, O_WRONLY); // Open FIFO for write only
        printf("User1: ");
        fgets(arr2, 80, stdin);//Take an input from user
        write(fd, arr2, strlen(arr2)+1); //Write to fifo
        close(fd); //Close the write fifo
        fd = open(fifoPath, O_RDONLY); // Open fifo for reading
        read(fd, arr1, sizeof(arr1)); // read from fifo to arr1
        printf("User2: %s\n", arr1);
        close(fd);
    }
    return 0;
}