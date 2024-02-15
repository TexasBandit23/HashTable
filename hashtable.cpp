#include <iostream>
#include <cstring>
#include "Node.h"
#include "student.h"
#include <iomanip>
#include <array>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;

void rehash(Node* tempNode, Node ** &hash, Node ** & newHash, int index, bool &rehash);
void add(int ID, float GPA, char first[30], char last[30], int &size, Node** &hash);
void print(Node ** hash, int &size);
void hashCall(int &size, int currentsize, Node** &hash, bool &rehash);

int main(){
  Node* head = NULL;
  bool running = true;

  Node** hash = new Node* [100];
  int size = 100;
  for(int i = 0; i < 100; i++){
    hash[i] = NULL;
  }
  
//while loop where code runs
  while (running == true){
    cout << "Enter 'ADD', 'PRINT', 'DELETE', or 'QUIT'" << endl;
    char input[15];
    for(int i = 0; i < 7; i++){
      input[i] = '\0';
    }
    cin.get(input, 15);
    cin.ignore(15, '\n');
    //if statements that determine what happens based on which function is called.
    if(strcmp(input, "ADD") == 0){
      //collecting information from the user about the student
      int ID;
      float GPA;
      char first[30];
      char last[30];
      cout << "What is the student's first name? " << endl;
      cin.get(first, 30);
      cin.get();
      cout << "What is the student's last name? " << endl;
      cin.get(last, 30);
      cin.get();
      cout << "What is the student's ID? " << endl;
      cin >> ID;
      cin.get();
      cout << "What is the student's GPA? " << endl;
      cin >> GPA;
      cin.get();
      
      add(ID, GPA, first, last, size, hash);

    }
    if(strcmp(input, "PRINT") == 0){
      print(hash, size);
    }
    if(strcmp(input, "QUIT") == 0){
      running = false;
    }
    if(strcmp(input, "DELETE") == 0){
      //delete function to be implemented
    }
  }
  return 0;
}

void add(int ID, float GPA, char first[30], char last[30], int &size, Node** &hash){
  student* newstudent = new student();

  newstudent->setID(ID);
  strcpy(newstudent->first, first);
  strcpy(newstudent->last, last);
  
  newstudent->setGPA(GPA);
  
  Node* tempNode = new Node();
  tempNode->setStudent(newstudent);
  
  int index = newstudent->getId() % size;

  if(hash[index] == NULL){
    hash[index] = tempNode;
  }
  else if(hash[index]->getNext() == NULL){
    hash[index]->setNext(tempNode);
  }
  else if(hash[index]->getNext()->getNext()==NULL){
    hash[index]->getNext()->setNext(tempNode);
  }
  else{
    bool rehash = true;
   
    hash[index]->getNext()->getNext()->setNext(tempNode);
    while(rehash == true){
      hashCall(size, size*2, hash, rehash);
    }

  }

  return;
}

void hashCall(int &size, int currentsize, Node** &hash, bool &rehash){
  
  rehash = false;
  
  Node** newHash = new Node*[currentsize];
  for(int i = 0; i < currentsize; i++){
    newHash[i] = NULL;

  }

  
  for(int i = 0; i < size; i++){
    
    Node* tempNode = hash[i];
    Node* secondTempNode = NULL;
    Node* thirdTempNode = NULL;
    Node* fourthTempNode = NULL;
    if(tempNode->getNext() != NULL){
      secondTempNode = tempNode->getNext();
      if(tempNode->getNext()->getNext() != NULL){
        thirdTempNode = tempNode->getNext()->getNext();
        if(tempNode->getNext()->getNext()->getNext() != NULL){
          fourthTempNode = tempNode->getNext()->getNext()->getNext();
        }
      }
    }
    
    int index;
    if(fourthTempNode != NULL){
      index = fourthTempNode->getStudent()->getId() % currentsize;
      rehash(fourthTempNode, hash, newHash, index, rehash);
      tempNode->getNext()->getNext()->setNext(NULL);
    }
    if(thirdTempNode != NULL){
      index = thirdTempNode->getStudent()->getId() % currentsize;
      rehash(thirdTempNode, hash, newHash, index, rehash);
      tempNode->getNext()->setNext(NULL);
    }
    if(secondTempNode != NULL){
      index = secondTempNode->getStudent()->getId() % currentsize;
      rehash(secondTempNode, hash, newHash, index, rehash);
      tempNode->setNext(NULL);
    }
    if(tempNode != NULL){
      index = tempNode->getStudent()->getId() % currentsize;
      rehash(tempNode, hash, newHash, index, rehash);
    }
    

  }
  size = size * 2;
  delete [] hash;
  hash = newHash;
  return;

}

void rehash(Node* tempNode, Node ** &hash, Node ** & newHash, int index, bool &rehash){
  int iterator = 0;
  if(newHash[index] == NULL){
    newHash[index] = tempNode;
  }
  
  else{
    Node* finalNode = newHash[index];
    while(finalNode->getNext() != NULL){
      finalNode = finalNode->getNext();
      iterator++;
    }
    if(iterator == 3){
      rehash = true;
    }
    finalNode->setNext(tempNode);
  }
  tempNode->setNext(NULL);


}

void print(Node ** hash, int &size){
  for(int i = 0; i < size; i++){
    if(hash[i] != NULL){
      cout << hash[i]->getStudent()->print() << endl;
      if(hash[i]->getNext() != NULL){
        cout << hash[i]->getNext()->getStudent()->print() << endl;
        if(hash[i]->getNext()->getNext()!=NULL){
          cout << hash[i]->getNext()->getNext()->getStudent()->print() << endl;
        }

      }


   }
  }
  return;

}
