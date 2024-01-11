#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>

#define SIZE_MEMORY     100             // the size (in bytes) of shared memory object
#define NAME_FILE       "tris_map"      // name of the shared memory object

int main() {
    int shm_fd = shm_open(NAME_FILE, O_CREAT | O_RDWR, 0666);
    if (shm_fd < 0) {
        printf("Create share memnory by shm_open() is failed ! --- %s\n", strerror(errno));
        return -1;
    }

    ftruncate(shm_fd, SIZE_MEMORY);

    char *data = (char *)mmap(0, SIZE_MEMORY, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    printf("\nRead data from share memmory: ");
    printf("%s\n", data);

    munmap(data, SIZE_MEMORY);

    close(shm_fd);
    return 0;
}