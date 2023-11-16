#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd, wr;
    char buff[12] = "test APPEND";

    fd = open("text.txt",O_RDWR | O_APPEND, 0777);
    if (fd == -1)
    {
        printf("open() file text.txt failed\n");
    }

    lseek(fd, 0, SEEK_SET);

    wr = write(fd, buff, strlen(buff));
    if (wr == -1)
    {
        printf("write() file text.txt failed\n");
    }
}

/*
Question: Viết một chương trình mở một file bất kì và sử dụng cờ O_APPEND, sau đó thực hiện seek về đầu file rồi ghi một vài dữ liệu vào file đó. Dữ liệu sẽ xuất hiện ở vị trí nào của file và tại sao lại như vậy?

Answer: 
O_APPEND
    The file is opened in append mode.  Before each write(2), the file offset is positioned at the end of the file, as if with lseek(2). 

-> Nghĩa là trước khi bắt đầu mỗi system call write(), địa chỉ con trỏ offset luôn đặt ở cuối tệp với cờ O_APPEND, dù cho có lseek(fd, 0, SEEK_SET) thì con trỏ vẫn ở cuối tệp. Nếu không có cờ Ô_APPEND thì con trỏ sẽ ở vị trí đầu file như đã set ở lệnh lseek.
*/