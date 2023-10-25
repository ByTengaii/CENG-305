#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h> 
#include <unistd.h>
#include <string.h>

int main()
{
    //* Const
    const int SIZE = 4096;
    const char *name = "OS";

    //* Messages that write to shared memory
    const char *message_0 = "Hello";
    const char *message_1 = "World";

    int shm_fd; // Shared mememory file descriptor
    void *ptr; // pointer to shared memory object

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); // Open shared memory with read and write

    // Resize the shared memory object
    if (ftruncate(shm_fd, SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    //PROTection_WRITE
    //MAP_SHARED : The memory can visible from other process
    // 0 : The system decide where at to start, end

    //* Write to shared memory
    sprintf(ptr, "%s", message_0);
    ptr += strlen(message_0);
    sprintf(ptr, "%s", message_1);
    ptr += strlen(message_1);

    return 0;
}

    // The flags argument is a bitwise OR of a permission mode and any of the following flags:
    // - O_CREAT: If the shared memory object does not exist, create it.
    // - O_EXCL: If O_CREAT is set and the shared memory object already exists, fail and return an error.
    //int flags = O_CREAT | O_EXCL | O_RDWR;

     // The mode argument specifies the permissions for the new shared memory object.
    //mode_t mode = S_IRUSR | S_IWUSR; // Read and write permission for the user