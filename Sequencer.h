//Title: Sequencer.h
//Author: Hazael Magino
//Date: 3/14/2023
//Description: This is part of the Transcription and Translation Project in CMSC 202 @ UMBC

// Do NOT edit this file

#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "Strand.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class Sequencer {
 public:
  // Name: Sequencer (constructor)
  // Desc: Creates a new sequencer to hold one or more DNA/mRNA strands make of
  //       multiples of three nucleotides
  // Preconditions:  Populates m_fileName from passed information from call
  //                 For example: ./proj3 proj3_data1.txt
  // Postconditions: A sequencer created to populate DNA/mRNA strands
  Sequencer(string fileName);
  // Name:  Sequencer (destructor)
  // Desc: Deallocates all dynamic aspects of a Sequencer
  // Preconditions: There are an existing DNA/mRNA strand(s) (linked list)
  // Postconditions: All vectors are cleared of DNA and mRNA strands
  //                 Indicates that the strands have been deallocated
  ~Sequencer();
  // Name: StartSequencing
  // Desc: Calls ReadFile and continually calls mainmenu until the user exits
  // Preconditions: m_fileName has been populated
  // Postconditions: m_DNA has been populated (after ReadFile concludes)
  void StartSequencing();
  // Name: DisplayStrands
  // Desc: Displays each strand in both mDNA and mRNA
  //       Displays numbered type (For example, DNA 1) then the name of the strand.
  //       Finally displays the strand with arrows between each nucleotide
  // Preconditions: At least one linked list is in mDNA (may have mRNA)
  // Postconditions: Displays DNA strand from one of the vectors
  void DisplayStrands();
  // Name: ReadFile
  // Desc: Reads in a file of DNA strands that has the name on one line then
  //       the sequence on the next
  //       All sequences will be an indeterminate length (always evenly divisible by three though).
  //       There are an indeterminate number of sequences in a file.
  //       Hint: Read in the entire sequence into a string then go char
  //       by char until you hit a new line break. Then insert to the m_DNA vector
  // Preconditions: Valid file name of characters (Filled with a name and then A, T, G, or C)
  // Postconditions: Populates each DNA strand and puts in m_DNA
  void ReadFile();
  // Name: MainMenu
  // Desc: Displays the main menu and manages exiting.
  //       Returns 5 if the user chooses to quit, else returns 0
  // Preconditions: m_DNA populated
  // Postconditions: Indicates the user has quit the program
  int MainMenu();
  // Name: ChooseDNA
  // Desc: Asks the user to choose one strand to use from loaded DNA strands
  // Preconditions: Populated m_DNA
  // Postconditions: Returns index of chosen strand
  int ChooseDNA();
  // Name: ChooseMRNA
  // Desc: Asks the user to choose one strand to use from translated mRNA strands
  // Preconditions: Populated m_mRNA
  // Postconditions: Returns index of chosen strand
  int ChooseMRNA();
  // Name: ReverseSequence
  // Desc: User chooses to reverse either DNA or mRNA to reverse
  //       Then calls either ChooseDNA or ChooseMRNA which returns index of strand
  //       Calls ReverseStrand on chosen location
  // Preconditions: Populated m_DNA or m_mRNA
  // Postconditions: Reverses a specific strand replacing in place
  void ReverseSequence();
  // Name: Transcribe
  // Desc: Iterates through each DNA strand in m_DNA to transcribe to m_mRNA
  // A->U, T->A, C->G, G->C (DNA to mRNA)
  // Can be called multiple times (will result in multiple mRNA strands)
  // Puts the transcribed mRNA strand into m_mRNA
  // Note: if this function is called more than once on the same strands of DNA,
  // it will add duplicate strands into m_mRNA!
  // Preconditions: Populated m_DNA
  // Postconditions: Transcribes each strand of m_DNA to m_mRNA
  void Transcribe();
  // Name: Translate
  // Desc: Iterates through a chosen mRNA strand and converts to amino acids
  // For every three nucleotides in strand, passes them three at a time to Convert
  // Displays each amino acid but does not store the amino acids in the class
  // Preconditions: Populated m_mRNA
  // Postconditions: Translates a specific strand of mRNA to amino acids
  void Translate();
  // Name: Convert (Provided)
  // Desc: Converts codon (three nodes) into an amino acid
  // Preconditions: Passed exactly three U, A, G, or C
  // Postconditions: Returns the string name of each amino acid
  string Convert(const string);
private:
  vector<Strand*> m_DNA; //Stores all DNA strands
  vector<Strand*> m_mRNA; //Stores all mRNA strands
  string m_fileName; //File to read in
};

#endif
