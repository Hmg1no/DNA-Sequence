// File:    Strand.cpp
// Author:  Hazael Magino
// Date:    3/28/2023
// Section: Section 12
// E-mail:  hazaelm1@umbc.edu
// Description: The goal of this we will be to model the transcriptions and translate of a DNA sequence. This program will load in a single strand of DNA 
// (picturing that the DNA has already been spliced) at a time. The DNA will then be transcribed into mRNA. 
// Finally, the mRNA will be converted into polypeptides using translation. Every three nucleotides, called a codon, will translate into one amino acid 


#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include <string>
#include "Strand.h"

using namespace std;


Strand::Strand(){
  // Name: Strand() - Default Constructor
  // Desc: Used to build a new empty strand (m_head, m_tail = nullptr and size = 0)
  // Preconditions: None
  // Postconditions: Creates a new strand with a default name

  m_name = "default strand";

  m_head = nullptr;

  m_tail = nullptr;

  m_size = 0;

}

Strand::Strand(string name){
  // Name: Strand(string) - Overloaded Constructor
  // Desc: Used to build a new empty strand with the name passed
  //       with m_head, m_tail = nullptr; size = 0;
  // Preconditions: None
  // Postconditions: Creates a new strand with passed name

  m_name = name;

  m_head = nullptr;

  m_tail = nullptr;

  m_size = 0;

}

Strand::~Strand(){
  // Name: ~Strand() - Destructor
  // Desc: Used to destruct a strand
  // Preconditions: There is an existing strand with at least one node
  // Postconditions: Strand is deallocated (including all dynamically allocated nodes)
  // to have no memory leaks!

  Node *curr = m_head; //creating new node

  while(curr != nullptr){ 
    
    // while loop to delete nodes while keep track of 
    // where it is in linked list and deallocate memory

    m_head = curr;

    curr = curr ->m_next;

    delete m_head;
  }

  //Default values

  m_head = nullptr; 

  m_tail = nullptr;
  
  m_size = 0;


}

void Strand::InsertEnd(char data){
  // Name: InsertEnd
  // Desc: Takes in a char. Creates a new node.
  //       Inserts node at the end of the strand. Increases size.
  // Preconditions: Requires a strand
  // Postconditions: Strand is larger.

//Create a new node

Node *newNode = new Node(); 

// Insert data into that node

newNode ->m_data = data; 

newNode ->m_next = nullptr;

if(m_head == nullptr){// special case (if it is the first node to be created (aka empty linked list)

  m_head = newNode;

  m_tail = newNode;


} else{

  m_tail-> m_next = newNode;
  
  m_tail = newNode;

}

// Increase size of linked list

m_size++;


}

string Strand::GetName(){
  // Name: GetName()
  // Preconditions: Requires a strand
  // Postconditions: Returns m_name;

  return m_name;

}

int Strand::GetSize(){
  // Name: GetSize()
  // Preconditions: Requires a strand
  // Postconditions: Returns m_size;

  return m_size;

}

void Strand::ReverseStrand(){
  // Name: ReverseSequence
  // Preconditions: Reverses the strand
  // Postconditions: Strand sequence is reversed in place; nothing returned

  Node *prev = nullptr;
  Node *curr = m_head;
  Node *next = nullptr;


  // Traverse the linked list between nodes

  while(curr != nullptr){


    //store the next node before changing the link of the current node

    next = curr->m_next;

    //Reverse the link of the current node to point to the previous node.

    curr->m_next = prev;

    //Move the pointers to the next nodes in the list.

    prev = curr;

    curr = next;

  }

  // Update the head pointer and tail pointer of the linked list to point to the last node and first node respectively.

  m_tail = m_head;

  m_head = prev;

}

char Strand::GetData(int nodeNum){
  // Name: GetData
  // Desc: Returns the data at a specific location in the strand.
  //       Iterates to node and returns char.
  // Preconditions: Requires a DNA sequence
  // Postconditions: Returns a single char from a node


  Node* currentNode = m_head; // create a pointer Node type variable to traverse linked list

  for (int i = 0; ((i < nodeNum ) && (currentNode != nullptr)); i++){

    if(currentNode == nullptr){ // if the identified node is outside

      return '\0';
    }

    currentNode = currentNode->m_next;

  }

  if (currentNode != nullptr){

    return currentNode -> m_data;

  }else{

    return '\0'; 
  }

}


ostream &operator<< (ostream &output, Strand &heapV){
  // Name: operator<<
  // Desc: Overloaded << operator to return ostream from strand
  //       Iterates over the entire strand and builds an output stream
  //       (Called like cout << *m_DNA.at(i); in Sequencer)
  // Preconditions: Requires a strand
  // Postconditions: Returns an output stream (does not cout the output)

  Node* currentNode = heapV.m_head; // start at the head of the linked list

  while(currentNode != nullptr){

    output << currentNode ->m_data << "->";

    currentNode = currentNode ->m_next;

  }

  output <<"END";
  return output;

}