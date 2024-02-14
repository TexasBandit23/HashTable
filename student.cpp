#include <iostream>
#include <iomanip>
#include "student.h"
#include <cstring>

using namespace std;

Student::Student() {
  // Initialize variables in the constructor
  strcpy(first, "");
  strcpy(last, "");
  ID = 0;
  GPA = 0.0;
}

//get the first name of a student
char* Student::getFirst() {
  return first;
}

//get the last name of a student
char* Student::getLast() {
  return last;
}

//could have also written setFirst and setLast functions but, chose not to

//get the id of a student
int Student::getID() {
  return ID;
}

//set the id of a student
void Student::setID(int nextID) {
  ID = nextID;
}

//get the GPA of a student
float Student::getGPA() {
  return GPA;
}

//set the GPA of a student
void Student::setGPA(float nextGPA) {
  GPA = nextGPA;
}

//print out a student and all of their information, not needed but much more efficient
void Student::print() {
  cout << first << " " << last << ", " << ID << ", " << fixed << setprecision(2) << GPA << endl;
}
