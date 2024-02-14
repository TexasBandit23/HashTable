#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student {

public:
  //prototypes for functions of student class
  //code may have been more efficient and more concise if a setFirst and setLast function were used
  Student();
  char* getFirst();
  char* getLast();
  int getID();
  void setID(int nextID);
  float getGPA();
  void setGPA(float nextGPA);
  void print(); //prints out a student and all of their data

private:
  //variables are all private
  char first[81];
  char last[81];
  int ID;
  float GPA;
};

#endif
