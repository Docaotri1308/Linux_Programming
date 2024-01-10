This is README file for Exer3 and Exer4.
Author: Do Cao Tri

Exer3: 
- Create file test.txt and write any data. 
- Write information on the screen: 
    + File type 
    + File name 
    + Last file modification time 
    + Size 
--> (Using struct stat)

Exer4: 
- Write a program that opens any file and uses the O_APPEND flag.
- Then does a seek to the beginning of the file and writes some data to that file.
- Where in the file will the data appear and why?

Answer: 
O_APPEND
    The file is opened in append mode.  Before each write(2),
    the file offset is positioned at the end of the file, as
    if with lseek(2).

--> This means that before starting each system call write(), the pointer address is always offset
set at the end of the file with the O_APPEND flag, even with lseek(fd, 0, SEEK_SET) the pointer is still at the end of the file.
Without the O_APPEND flag, the pointer will be at the beginning of the file as set in the lseek command.