//Code from Rowan Miller
/*
*Note: I have modified the code that was sent to me. The code originally had print statements in every
function that executed each time the functions were called. These print functions inmpacted my code so, I
commented them out. 
*/

#include <iostream>
#include "node.h"
#include <cstring>
#include <vector>
#include "student.h"

using namespace std;

//creates the node 
Node::Node(Student* myStudent) {
  student = myStudent; 
  next = NULL;
  //cout << "constucting" << endl;
}

//deletes the student
Node::~Node() {
  delete student;
  next = NULL;
  //cout << "destructing" << endl; 
}

//gets the next node
Node* Node::getNext() {
  //cout << "getting next" << endl; 
  return next;
}

//sets the next node
void Node::setNext(Node* nextNode) {
  next = nextNode;
  //cout << "setting next" << endl; 
}

//gets the student
Student* Node::getStudent() {
  //cout << "getting student" << endl; 
  return student; 
}

