This is README file for Exer17.
Author: Do Cao Tri

Exer17:
- Creates a list of new student message queues. The format of data stored in queues is as follows:
    typedef struct {
        char Name[50];
        int Age;
        char PhoneNum[50];
        char Home[50];
    } Human;

    typedef struct {
        long prio_id;
        Human Human;
    } Message;

- Menu displays functions.
- Enter student information from the keyboard and store it in the queue.
- Display student information via id.
- Displays the entire list of students.
- Remove a student from the list via id.
- Note: each student's id value is unique and greater than 0.

Note: build main.c to excutable file, remember the linking "-Wall -lrt" option