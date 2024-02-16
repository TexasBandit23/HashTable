//Code from Rowan Miller

#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>
#include <vector>
#include "student.h"

using namespace std;

class Node {
public:
  //constructors for methods used in node.cpp
  Node(Student* myStudent);
  ~Node();
  Node* getNext();
  void setNext(Node* nextNode); 
  Student* getStudent();
protected: //I am assuming protected is the same thing as private
  //private variables used in node.cpp
  Node* next;
  Student* student; 
};
#endif
