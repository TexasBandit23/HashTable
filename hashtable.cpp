
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
void add(int Id, float GPA, char first[30], char last[30], int &size, Node** &hash);
void remove(Node* &head, Node* current, Node* prev, int deleteID);
void hash(int &size, int currentsize, Node** &hash, bool &rehash);

int main(){
  Node* head = NULL;
  bool running = true;


  int size = 100;
  Node** hash = new Node* [100];
  for(int i = 0; i < 100; i++){
    hash[i] = NULL;
    
  }

  while (running == true){
    cout << "Enter 'ADD', 'PRINT', 'DELETE', or 'QUIT'" << endl;
    char input[15];
    for(int i = 0; i < 7; i++){
      input[i] = '\0';
    }
    cin.get(input, 15);
    cin.ignore(15, '\n');
    if(strcmp(input, "ADD") == 0){
      int ID;
      float GPA;
      char first[30];
      char last[30];
      cout << "First name? " << endl;
      cin.get(first, 30);
      cin.get();
      cout << "Last name? " << endl;
      cin.get(last, 30);
      cin.get();
      cout << "ID? " << endl;
      cin >> ID;
      cin.get();
      cout << "GPA? " << endl;
      cin >> GPA;
      cin.get();
      
      add(ID, GPA, first, last, size, hash);

    }
    if(strcmp(input, "PRINT") == 0){
      //call print
    }
    if(strcmp(input, "QUIT") == 0){
      stillRunning = false;
    }
    if(strcmp(input, "DELETE") == 0){
      cout << "What ID would you like to delete?" << endl;
  
      int deleted;
      cin >> deleted;
      cin.get();
      int index = deleted % size;
      
      remove(hash[index], hash[index], hash[index], deleted);
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
      hashFunction(size, size*2, hash, rehash);
    }

  }

  return;
}


void hash(int &size, int currentsize, Node** &hash, bool &rehash){
  
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
    
    int index;
    if(fourthTempNode != NULL){
      index = fourthTempNode->getStudent()->getId() % currentsize;
      rehashMechanics(fourthTempNode, hash, newHash, index, rehash);
      tempNode->getNext()->getNext()->setNext(NULL);
    }
    if(thirdTempNode != NULL){
      index = thirdTempNode->getStudent()->getId() % currentsize;
      rehashMechanics(thirdTempNode, hash, newHash, index, rehash);
      tempNode->getNext()->setNext(NULL);
    }
    if(secondTempNode != NULL){
      index = secondTempNode->getStudent()->getId() % currentsize;
      rehashMechanics(secondTempNode, hash, newHash, index, rehash);
      tempNode->setNext(NULL);
    }
    if(tempNode != NULL){
      index = tempNode->getStudent()->getId() % currentsize;
      rehashMechanics(tempNode, hash, newHash, index, rehash);
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
    if(iterator == 4){
      rehash = true;
    }
    finalNode->setNext(tempNode);
  }
  tempNode->setNext(NULL);


}


void remove(Node* &head, Node* current, Node* prev, int deleteID){
  
  if(head == NULL){
    return;
  }
  
  else{
   
    if(current->getStudent()->getId() == deleteID){
      if(current == head){
        Node* tempNode = current->getNext();
        delete head;
        head = tempNode;
      }
      else{
        prev->setNext(current->getNext());
        delete current;
      }
    }
    
    else{
      if(current->getNext()!= NULL){
        remove(head, current->getNext(), current, deleteID);
      }
      else{
        return;
      }
      return;
    }
  }
}

