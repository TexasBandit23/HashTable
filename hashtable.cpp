/*
Author: Tejas Pandit
Last Edited: 2/15/24
This program is a variation of student list. However, it is done using a hashtable, which is just an array of
linkedlists. When one entry of the table gets too big, the hashtable will expand in size
Worked with Jazveer Kaler and got help from Vikram Vasudevan
 */

//imports
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
#include <limits>

using namespace std;

//function prototypes
void print(Node** &hash, int &size);
void add(Student* student, int &size, Node** &hash);
void remove(Node** &hash, int &size, int removeID);
void hashFunction(int size, Node** &hash, bool &needRehash);
void rehashFunction(Node** &hash, int &size);
void randomGenerator(Node** &hash, int &size, vector<char*> first, vector <char*> last);

int main() {
    //initialize variables
    char input[81];
    bool stillRunning = true;
    Node* head = nullptr;

    //create hash table
    Node** hash = new Node* [100];
    for (int i = 0; i < 100; i++) {
        hash[i] = nullptr;
    }

    //read in names from files and put them in an array
    vector<char*> first;
    vector<char*> last;
    
    fstream first_stream;
    fstream second_stream;
    
    //reading in files
    first_stream.open("firstname.txt");
    for(int i = 0; i < 25; i++){
        char* temp = new char [15];
        first_stream.getline(temp, 15);
        first.push_back(temp);
    }
    
    first_stream.close();
    
    second_stream.open("lastname.txt");
    for(int i = 0; i < 25; i++){
        char* temp = new char[15];
        second_stream.getline(temp, 15);
        last.push_back(temp);
    }
    
    bool needRehash = false;
    int size = 100;
    
    cout << "This is student list using a Hash Table" << endl;

    //runs until QUIT is entered
    while (stillRunning == true) { 

        //get user input
        cout << "Type in a command: ADD, PRINT, DELETE, RANDOM, or QUIT" << endl;
        cin.get(input, 81);
        cin.ignore(81, '\n');

	//call print function
        if (strcmp(input, "PRINT") == 0) {
            cout << "Printing...: " << endl;
            print(hash, size);
        }
	
        //ask for user input and call add function
        else if (strcmp(input, "ADD") == 0) {
            Student* student = new Student();
            
            //take in information
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
            
            //check if we need to rehash after the student is added
            hashFunction(size, hash, needRehash);
            
            if (needRehash == true) {
	        //if we need to rehash, do so
                rehashFunction(hash, size);
                needRehash = false;
            }
        }

        //call delete function by asking for the ID to be removed
        else if (strcmp(input, "DELETE") == 0) {
            cout << "What ID would you like to delete?" << endl;

            int removeID;
            cin >> removeID;
            cin.get();

            remove(hash, size, removeID);
            
            //check if rehashing is needed
            hashFunction(size, hash, needRehash);
            if (needRehash == true) {
                rehashFunction(hash, size);
                needRehash = false;
            }
        }
        //call the random function to generate a certain amount of random students
        else if (strcmp(input, "RANDOM") == 0) {
	  randomGenerator(hash, size, first, last);
	  cin.ignore(numeric_limits<streamsize>::max(), '\n'); //this line is needed to prevent an infinite loop
        }



        //break while loop if QUIT is entered
        else if (strcmp(input, "QUIT") == 0) {
            cout << "Bye..." << endl;
            stillRunning = false;
        }
    }

}
//add function
void add(Student* student, int &size, Node** &hash) {
  Node* node = new Node(student);
  int value = student->getID() % size; //find where to put the student in the table

  //check if the student needs to be linked to another
  if (hash[value] == nullptr) {
      hash[value] = node;
  } else {
      node->setNext(hash[value]);
      hash[value] = node;
  }

  cout << "Added..." << endl;
}
//remove function
void remove(Node** &hash, int &size, int removeID) {
    int value = removeID % size; //find teh index of the student to be removed
    Node* previousNode = nullptr;
    Node* currentNode = hash[value];

    //once index has been found, iterate through links until student is found and delete
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
	//preserve the linked list
        previousNode = currentNode;
        currentNode = currentNode->getNext();
    }

    cout << "ID: " << removeID << " not found." << endl;
}

//print function
void print(Node** &hash, int &size) {
    //iterate through the whole table and all links and print each student and their information
    for (int i = 0; i < size; i++) {
        Node* currentNode = hash[i];
        while (currentNode != nullptr) {
            currentNode->getStudent()->print();
            currentNode = currentNode->getNext();
        }
    }
}

//generate random students function
void randomGenerator(Node** &hash, int &size, vector<char*> first, vector <char*> last) {

    int numPersons = 0;
    cout << "How many students do you want to generate: " << endl;
    cin >> numPersons;
    
    srand(time(NULL));

    //starting ID that is to be iterated
    int ID = 100000;
    
    cout << "Number of students to generate: " << numPersons << endl;
    
    for(int i = 0; i < numPersons; i++) {
        cout << "Generating student " << i+1 << " of " << numPersons << endl;
        int randNum1 = rand()%25;
        int randNum2 = rand()%25;

	//random GPA
        float randGPA = (float) (rand()%(100-1+1) + 1)/25;
        
        Student* randStudent = new Student();
	
        //cout << first.at(randNum1) << endl;
        //cout << last.at(randNum2) << endl;

	//set ID, GPA, and name of student to be random
        randStudent->setFirst(first.at(randNum1));
        randStudent->setLast(last.at(randNum2));
        randStudent->setID(ID);
        ID++;
        randStudent->setGPA(randGPA);
        add(randStudent, size, hash);
        
        cout << "Adding student " << randStudent->getFirst() << " " << randStudent->getLast() << endl;
    }
    
    cout << "Students added..." << endl;
    return;
}

//hash function
void hashFunction(int size, Node** &hash, bool &needRehash) {
    int currentNumberOfLinks = 0;
    int maximumNumberOfLinks = 3;

    //find if a table entry has more than 3 links
    for (int i = 0; i < size; ++i) {
        Node* currentNode = hash[i];
        while (currentNode != nullptr) {
            currentNode = currentNode->getNext();
	    currentNumberOfLinks++;
        }
	//if there are too many links, we need to rehash
	if (currentNumberOfLinks > maximumNumberOfLinks) {
	  needRehash = true;
	}
	//reset the number of links to check the next entry
	currentNumberOfLinks = 0;
    }
}

//rehash function
void rehashFunction(Node** &hash, int &size) {
    //we need to double the size of the hash table 
    int doubleSize = size * 2;
    Node** doubleHash = new Node*[doubleSize];
    
    // New hash table
    for (int i = 0; i < doubleSize; ++i) {
        doubleHash[i] = nullptr;
    }
    
    //rehash and add in students to be more spread out
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
       
    //change variables
    delete[] hash;
    hash = doubleHash;
    size = doubleSize;

    cout << "New size: " << doubleSize << endl;
}
