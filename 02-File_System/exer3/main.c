#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

int main()
{
    int fd;
    char buff[18] = "Hello Mr.Phong !\n";
    int rd, wr;

    struct stat infor;

    fd = open("test.txt", O_RDWR | O_CREAT, 0777);
    if (fd == -1)
    {
        printf("open() file test.txt failed\n");
    }

    wr = write(fd, buff, strlen(buff));
    if (wr == -1)
    {
        printf("write() file test.txt failed\n");
    }

    printf("File Name: Test.txt\n");

    printf("File Type: ");
    switch (infor.st_mode & __S_IFMT)
    {
    case __S_IFBLK:
        printf("block device\n");
        break;
    case __S_IFCHR:
        printf("character device\n");
        break;
    case __S_IFDIR:
        printf("directory\n");
        break;
    case __S_IFIFO:
        printf("FIFO/pipe\n");
        break;
    case __S_IFLNK:
        printf("symlink\n");
        break;
    case __S_IFREG:
        printf("regular file\n");
        break;
    case __S_IFSOCK:
        printf("socket\n");
        break;
    default:
        printf("unknown?\n");
        break;
    }

    printf("File Last Modification: %s\n", ctime(&infor.st_mtime));
    printf("File Size: %ld\n", infor.st_size);

    close(fd);
    return 0;
}