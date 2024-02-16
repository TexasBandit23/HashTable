#include <cctype>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>
#include "node.h"
#include "student.h"
#include <array>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

// Function prototypes
void print(Node** &hash, int &size);
void add(Student* student, int &size, Node** &hash);
void remove(Node** &hash, int &size, int removeID);
void hashFunction(int size, Node** &hash, bool &needRehash);
void rehashFunction(Node** &hash, int &size);

int main() {
    char input[81];
    bool stillRunning = true;
    Node* head = nullptr; // Initializing head pointer to nullptr
    
    Node** hash = new Node* [100];
    for (int i = 0; i < 100; i++) {
        hash[i] = nullptr;
    }
  
    bool needRehash = false; // Initializing rehashNeeded variable
    int size = 100;
    
    cout << "This is student list using a Hash Table" << endl;

    // Main program loop
    while (stillRunning == true) { 

        // Takes in commands
        cout << "Type in a command: ADD, PRINT, DELETE, RANDOM, or QUIT" << endl;
        cin.get(input, 81);
        cin.ignore(81, '\n');

	// PRINT
        if (strcmp(input, "PRINT") == 0) {
            cout << "Printing...: " << endl;
            print(hash, size);
        }
	
        // ADD
        else if (strcmp(input, "ADD") == 0) {
            Student* student = new Student();
            
            //Takes in information
            cout << "First Name: " << endl;
            char firstName[81];
            cin.get(firstName, 81);
            cin.ignore(81, '\n');
            strcpy(student->getFirst(), firstName);
            
            cout << "Last Name: " << endl;
	    char lastName[81];
            cin.get(lastName, 81);
            cin.ignore(81, '\n');
            strcpy(student->getLast(), lastName);
            
            cout << "Student ID: " << endl;
            int ID;
            cin >> ID;
            cin.ignore(81, '\n');
            student->setID(ID);
            
            cout << "Student GPA: " << endl;
            float GPA;
            cin >> GPA;
            cin.ignore(81, '\n');
            student->setGPA(GPA);

            add(student, size, hash);
            
            // Check if rehashing is needed after adding or deleting
            hashFunction(size, hash, needRehash);
            
            if (needRehash == true) {
                rehashFunction(hash, size);
                needRehash = false;
            }
        }

        // DELETE
        else if (strcmp(input, "DELETE") == 0) {
            cout << "What ID would you like to delete?" << endl;

            int removeID;
            cin >> removeID;
            cin.get();

            remove(hash, size, removeID);
            
            // Check if rehashing is needed after adding or deleting
            hashFunction(size, hash, needRehash);
            if (needRehash == true) {
                rehashFunction(hash, size);
                needRehash = false;
            }
        }
        
        else if (strcmp(input, "RANDOM") == 0) {
            
        }



        // QUIT
        else if (strcmp(input, "QUIT") == 0) {
            cout << "Bye..." << endl;
            stillRunning = false;
        }
    }

}

void add(Student* student, int &size, Node** &hash) {
  Node* node = new Node(student);
  int value = student->getID() % size;

  // Chaining
  if (hash[value] == nullptr) {
      hash[value] = node;
  } else {
      node->setNext(hash[value]);
      hash[value] = node;
  }

  cout << "Added..." << endl;
}

void remove(Node** &hash, int &size, int removeID) {
    int value = removeID % size;
    Node* previousNode = nullptr;
    Node* currentNode = hash[value];

    while (currentNode != nullptr) {
        if (currentNode->getStudent()->getID() == removeID) {
            if (previousNode == nullptr) {
                hash[value] = currentNode->getNext();
            } else {
                previousNode->setNext(currentNode->getNext());
            }
            delete currentNode;
            cout << "Deleted...." << endl;
            return;
        }
        previousNode = currentNode;
        currentNode = currentNode->getNext();
    }

    cout << "ID: " << removeID << " not found." << endl;
}

// Print
void print(Node** &hash, int &size) {
    for (int i = 0; i < size; i++) {
        Node* currentNode = hash[i];
        while (currentNode != nullptr) {
            currentNode->getStudent()->print();
            currentNode = currentNode->getNext();
        }
    }
}


void hashFunction(int size, Node** &hash, bool &needRehash) {
    int currentNumberOfLinks = 0;
    int maximumNumberOfLinks = 3;

    // Calculate total collisions
    for (int i = 0; i < size; ++i) {
        Node* currentNode = hash[i];
        while (currentNode != nullptr) {
            currentNode = currentNode->getNext();
	    currentNumberOfLinks++;
        }
	if (currentNumberOfLinks > maximumNumberOfLinks) {
	  needRehash = true;
	}
	currentNumberOfLinks = 0;
    }
}

void rehashFunction(Node** &hash, int &size) {
    int doubleSize = size * 2;
    Node** doubleHash = new Node*[doubleSize];
    
    // New hash table
    for (int i = 0; i < doubleSize; ++i) {
        doubleHash[i] = nullptr;
    }
    
    // Rehash
    for (int i = 0; i < size; ++i) {
        Node* currentNode = hash[i];
        while (currentNode != nullptr) {
            Node* nextNode = currentNode->getNext();
            int value = currentNode->getStudent()->getID() % doubleSize;
            
            if (doubleHash[value] == nullptr) {
                doubleHash[value] = currentNode;
                currentNode->setNext(nullptr);
            } else {
                currentNode->setNext(doubleHash[value]);
                doubleHash[value] = currentNode;
            }
            currentNode = nextNode;
        }
    }
       
    // Update variables
    delete[] hash;
    hash = doubleHash;
    size = doubleSize;

    cout << "Hash table rehashed. New size: " << doubleSize << endl;
}
