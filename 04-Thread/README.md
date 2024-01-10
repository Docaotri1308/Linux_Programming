This is README file for Exer10 and Exer11 and Exer12.
Author: Do Cao Tri

Exer10:
- Provide an example where multi-thread does not provide better performance than single-thread solutions.

Exer11:
- Write a program to create 2 threads. Both of these threads use the same handler.
- Check if thread1 is executing, then print any message to determine.
- If it is thread2, then pass in data of struct human type that was initialized before, with information: Full name, year of birth, phone number, hometown. Then print this information to the screen.

Exer12:
Write a program to create 3 threads.
- Thread 1: Enter student data from the keyboard, including information: Full name, date of birth, hometown.
- Thread 2: Each time a student's data is entered, this thread will write that student's information into the file (each student's information is on 1 line) thongtinsinhvien.txt.
- Thread 3: Read the recorded data and print it to the screen then notify thread 1 to continue entering more students.
- Use mutex and condition variable to solve the problem.