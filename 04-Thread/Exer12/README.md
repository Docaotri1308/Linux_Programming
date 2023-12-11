This is README file for Exer12.
Author: Do Cao Tri

Exer12:
Write a program to create 3 threads.
- Thread 1: Enter student data from the keyboard, including information: Full name, date of birth, hometown.
- Thread2: Each time a student's data is entered, this thread will write that student's information into the file (each student's information is on 1 line) thongtinsinhvien.txt.
- Thread3: Read the recorded data and print it to the screen then notify thread 1 to continue entering more students.
- Use mutex and condition variable to solve the problem.