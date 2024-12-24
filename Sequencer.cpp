// File:    Sequencer.cpp
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
#include "Sequencer.h"
#include "Strand.h"


using namespace std;


  // Name: Sequencer (constructor)
  // Desc: Creates a new sequencer to hold one or more DNA/mRNA strands make of
  //       multiples of three nucleotides
  // Preconditions:  Populates m_fileName from passed information from call
  //                 For example: ./proj3 proj3_data1.txt
  // Postconditions: A sequencer created to populate DNA/mRNA strands
Sequencer::Sequencer(string fileName){

  //Set filename for readfile

m_fileName = fileName;

}


// Name:  Sequencer (destructor)
  // Desc: Deallocates all dynamic aspects of a Sequencer
  // Preconditions: There are an existing DNA/mRNA strand(s) (linked list)
  // Postconditions: All vectors are cleared of DNA and mRNA strands 
  //Indicates that the strands have been deallocated
Sequencer::~Sequencer(){

cout << "Exiting Program" << endl;

cout << "Deleting mDNA Strands" << endl;

// Loop through each DNA strnad and delete it using the 'delete' keyword 

for (unsigned int i = 0; i < m_DNA.size(); i++){

  delete m_DNA.at(i);
}

cout << "Deleting mRNA Strands" << endl;

// Loop through each mRNA strand and delete it using the 'delete' keyword

for (unsigned int i = 0; i < m_mRNA.size(); i++){

  delete m_mRNA.at(i);

}

  
}



  // Name: StartSequencing
  // Desc: Calls ReadFile and continually calls mainmenu until the user exits
  // Preconditions: m_fileName has been populated
  // Postconditions: m_DNA has been populated (after ReadFile concludes)
void Sequencer::StartSequencing(){

int state = 0;

  //Call the function to read the DNA sequences from the file

ReadFile();

  //Print out the number of DNA strands loaded in

cout  << m_DNA.size() << " Strand(s) loaded\n" << endl;

  // Continously call the main menu function

do{
    
  state = MainMenu();

}while(state == 0);

}

  // Name: DisplayStrands
  // Desc: Displays each strand in both mDNA and mRNA
  //       Displays numbered type (For example, DNA 1) then the name of the strand.
  //       Finally displays the strand with arrows between each nucleotide
  // Preconditions: At least one linked list is in mDNA (may have mRNA)
  // Postconditions: Displays DNA strand from one of the vectors
void Sequencer::DisplayStrands(){

    // Loop over each strand in the DNA vector

for (unsigned int i = 0; i < m_DNA.size(); i++) {

        cout << "DNA " << i + 1 << endl;
        
        cout << "*********" << m_DNA.at(i)->GetName() << "*********" << endl;

        // Print the DNA strand with arrows between each nucleotide

        cout  << *m_DNA.at(i) << endl;
    }

for (unsigned int i = 0; i < m_mRNA.size(); i++){

      // Check if the strand has an mRNA version

        if (m_mRNA.size() >= i ) { //must have an m_RNA strand to cout first condition

        // Print the mRNA strand with arrows between each nucleotide

            cout << "mRNA: " << i + 1<< endl;

            cout << "*********" << m_mRNA.at(i)->GetName() << "*********" << endl;

            cout << *m_mRNA.at(i) << endl;
        }

    }

}

  // Name: ReadFile
  // Desc: Reads in a file of DNA strands that has the name and the sequence on one line the
  //       All sequences will be an indeterminate length (always evenly divisible by three though).
  //       There are an indeterminate number of sequences in a file.
  //       Hint: Read in the entire sequence into a string then go char
  //       by char until you hit a new line break. Then insert to the m_DNA vector
  // Preconditions: Valid file name of characters (Filled with a name and then A, T, G, or C)
  // Postconditions: Populates each DNA strand and puts in m_DNA
void Sequencer::ReadFile(){


  ifstream inputData;

  inputData.open(m_fileName);
  
  if (inputData.is_open()){

  // Declare variables to hold name and sequence

  string name;
  
  string sequence; 

  // Loop over the file, reading each name and sequence on a line 

  while(getline(inputData, name,',') && getline(inputData, sequence)){

    //Create a new Strand object with the given name

    Strand *newStrand = new Strand(name);

    // Loop over the character in sequence, skipping commas and 

    for(int i = 0; i < sequence.length(); i++){
        
      if((sequence[i] != ',') && (sequence[i] != '\n')){

        // Insert the current nucleotide into the Strand object

        newStrand -> InsertEnd(sequence[i]);

      }

    }

    // Add the completed Strand object to the m_DNA vector

    m_DNA.push_back(newStrand);

  }

  }else{

    cout << "Error reading file" << endl;
    
  }

  //Close file once done reading

  inputData.close();

}



  // Name: MainMenu
  // Desc: Displays the main menu and manages exiting.
  //       Returns 5 if the user chooses to quit, else returns 0
  // Preconditions: m_DNA populated
  // Postconditions: Indicates the user has quit the program
int Sequencer::MainMenu(){

  const int EXIT = 5;

  int choice = 0;  

  // Displaying menu options

  cout << "What would you like to do?: " <<  endl; 

  cout << "1. Display Stands\n" << endl;

  cout << "2. Reverse Strand\n" << endl;

  cout << "3. Transcribe DNA to mRNA\n" << endl;

  cout << "4. Translate mRNA to Amino Acids\n" << endl;

  cout << "5. Exit\n" << endl;

  //Reading user choice from input

  cin >> choice;

    //Switch statement to determine which functions calls to make

    switch(choice){
        case 1:
        DisplayStrands();
        break;

        case 2:
        ReverseSequence();
        break;

        case 3:
        Transcribe();
        break;

        case 4:
        Translate();
        break;

        case 5:
        break;

        default:
        cout << "Invalid input. Please select something on the main menu" << endl;

    }



  // Return 0 if the user did not select exit from the menu options

  if(choice == EXIT){

    return EXIT;

  }else{

    return 0;

  }
} 


  // Name: ChooseDNA
  // Desc: Asks the user to choose one strand to use from loaded DNA strands
  // Preconditions: Populated m_DNA
  // Postconditions: Returns index of chosen strand
int Sequencer::ChooseDNA(){

  unsigned int choice = 0;

  if(m_DNA.size() == 1){ // if there is only 1 strand

    return 0;

  }else{


  do {

    cout << "Which strand would you like to work with?" << endl;

    cout << "Choose between: \n1 - " << m_DNA.size() << endl;

    cin >> choice;
  
  }while((choice < 1) || (choice > m_DNA.size()));

  }

  return choice - 1; // Subtract - 1 Because a vector is 0 based

  
}


  // Name: ChooseMRNA
  // Desc: Asks the user to choose one strand to use from translated mRNA strands
  // Preconditions: Populated m_mRNA
  // Postconditions: Returns index of chosen strand
int Sequencer::ChooseMRNA(){

  unsigned int choice = 0;

  if(m_mRNA.size() == 1){ // if there is only 1 strand available

    return 0;

  }else{


  do {

    cout << "Which strand would you like to work with?" << endl;

    cout << "Choose between: \n1 - " << m_mRNA.size() << endl;

    cin >> choice;
  
  }while((choice < 1) || (choice > m_mRNA.size()));

  }

  return choice - 1; // - 1 Because a vector is 0 based

}


  // Name: ReverseSequence
  // Desc: User chooses to reverse either DNA or mRNA to reverse
  //       Then calls either ChooseDNA or ChooseMRNA which returns index of strand
  //       Calls ReverseStrand on chosen location
  // Preconditions: Populated m_DNA or m_mRNA
  // Postconditions: Reverses a specific strand replacing in place
void Sequencer::ReverseSequence(){
  //const for DNA choosing

  const int DNA = 1;
  const int mRNA = 2;

  // variables for choice and indexing vector

  int choice = 0;
  int index = 0;

do {

  cout << "Which type of strand to reverse?\n1. DNA\n2. mRNA" << endl;

  cin >> choice;

}while((choice != DNA && choice != mRNA));

  if (choice == DNA){

    index = ChooseDNA();

    m_DNA.at(index)->ReverseStrand();

    cout << "Done reversing DNA " << index + 1 <<"'s. " <<endl;

}

if(choice == mRNA){

    if(m_mRNA.size() < 1){

      cout << "No mRNA to reverse; transcribe first" << endl;

      return;

}else{

    int index = 0;

    index = ChooseMRNA();

    m_mRNA.at(index)->ReverseStrand();

    cout << "Done reversing mRNA " << index + 1 <<"'s. " <<endl;

    }

  }

}


  // Name: Transcribe
  // Desc: Iterates through each DNA strand in m_DNA to transcribe to m_mRNA
  // A->U, T->A, C->G, G->C (DNA to mRNA)
  // Can be called multiple times (will result in multiple mRNA strands)
  // Puts the transcribed mRNA strand into m_mRNA
  // Note: if this function is called more than once on the same strands of DNA,
  // it will add duplicate strands into m_mRNA!
  // Preconditions: Populated m_DNA
  // Postconditions: Transcribes each strand of m_DNA to m_mRNA
void Sequencer::Transcribe(){

  //Declare and define const for nucleotides

  const char ADENINE = 'A';
  const char GUANINE = 'G';
  const char CYTOSINE = 'C';
  const char THYMINE = 'T';
  const char URACIL = 'U';

  //initialize and define variables 

  int x = 0;
  int y = 0;
  int sequenceSize = 0;

  //Loop through each DNA strand in the DNA vector

while(x < m_DNA.size()){

    //Create a new mRNA strand object with the same name as the current DNA strand

    Strand *tRNA= new Strand(m_DNA.at(x)->GetName());

    //Get the size of the current DNA strand

    sequenceSize =  m_DNA.at(x)->GetSize();

    //Loop through each nucleotide in the current DNA strand
    
    while(y < sequenceSize){

      //Get the current nucleotide in the DNA strand

      char newChar = m_DNA.at(x)->GetData(y);

      //Replace each nucleotide in the DNA strand with its corresponding nucleotide in the mRNA strand
      
      if(newChar == ADENINE){

        tRNA -> InsertEnd(URACIL);

        //Increment the index of the current nucleotide in the DNA strand

        y++;

      }

      if(newChar == THYMINE){

        tRNA -> InsertEnd(ADENINE);

        y++;
      }

      if(newChar == CYTOSINE){

        tRNA -> InsertEnd(GUANINE);

        y++;
      }

      if(newChar == GUANINE){

        tRNA -> InsertEnd(CYTOSINE);

        y++;

      }

    }

    //Add the completed mRNA strand to the output vector

    m_mRNA.push_back(tRNA);

    //Increment the index of thr current DNA strand

    x++;

    //Reset the index of the current nucleotide in the DNA strand

    y = 0;

}
  
  cout << x  << " strand(s) of DNA successfully transcribed into new mRNA strands" << endl;

}


  // Name: Translate
  // Desc: Iterates through a chosen mRNA strand and converts to amino acids
  // For every three nucleotides in strand, passes them three at a time to Convert
  // Displays each amino acid but does not store the amino acids in the class
  // Preconditions: Populated m_mRNA
  // Postconditions: Translates a specific strand of mRNA to amino acids
void Sequencer::Translate(){

  // initalize and declare variables 

  int choice = 0;
  int strandSize = 0;
  int c = 0; // iterator value of while loop
  int count = 0; // Varaible to help keep track of the count for every three node
  string codon = ""; //Variable to store the 3 chars as a string


  // Check if there are mRNA to translate

  if(m_mRNA.size() < 1){

    cout << "No mRNA to translate; transcribe first" << endl;

    return;

  }

  //choose which mRNA strand to translate

  choice = ChooseMRNA();

  //Get the size of the chose mRNA strand

  strandSize = m_mRNA.at(choice)->GetSize();
    
    cout << "*********" << m_mRNA.at(choice)->GetName() << "*********" << endl;

while(c < int(strandSize)){

      // Variable to store character from each node

      char Nucl = m_mRNA.at(choice)->GetData(c);

      //Add the nucleotides to the current codon

      codon+= Nucl;

      //increment counters

      c++;
      count++;

      if(count % 3 == 0){

        //Utilize convert function

        cout << codon << " -> " << Convert(codon) << endl;

        //Reset it to an empty string

        codon = "";

      }

    }

  cout << "Done translating mRNA " << choice + 1 << "'s strand."<< endl;

}




  // Name: Convert (Provided)
  // Desc: Converts codon (three nodes) into an amino acid
  // Preconditions: Passed exactly three U, A, G, or C
  // Postconditions: Returns the string name of each amino acid
string Sequencer::Convert(const string trinucleotide){

      if((trinucleotide=="AUU")||(trinucleotide=="AUC")||(trinucleotide=="AUA"))
    return ("Isoleucine");
  else if((trinucleotide=="CUU")||(trinucleotide=="CUC")||(trinucleotide=="CUA")||
          (trinucleotide=="CUG")|| (trinucleotide=="UUA")||(trinucleotide=="UUG"))
    return ("Leucine");
  else if((trinucleotide=="GUU")||(trinucleotide=="GUC")||
          (trinucleotide=="GUA")||(trinucleotide=="GUG"))
    return ("Valine");
  else if((trinucleotide=="UUU")||(trinucleotide=="UUC"))
    return ("Phenylalanine");
  else if((trinucleotide=="AUG"))
    return ("Methionine (START)");
  else if((trinucleotide=="UGU")||(trinucleotide=="UGC"))
    return ("Cysteine");
  else if((trinucleotide=="GCU")||(trinucleotide=="GCC")||
          (trinucleotide=="GCA")||(trinucleotide=="GCG"))
    return ("Alanine");
  else if((trinucleotide=="GGU")||(trinucleotide=="GGC")||
          (trinucleotide=="GGA")||(trinucleotide=="GGG"))
    return ("Glycine");
  else if((trinucleotide=="CCU")||(trinucleotide=="CCC")||
          (trinucleotide=="CCA")||(trinucleotide=="CCG"))
    return ("Proline");
  else if((trinucleotide=="ACU")||(trinucleotide=="ACC")||
          (trinucleotide=="ACA")||(trinucleotide=="ACG"))
    return ("Threonine");
  else if((trinucleotide=="UCU")||(trinucleotide=="UCC")||
          (trinucleotide=="UCA")||(trinucleotide=="UCG")||
          (trinucleotide=="AGU")||(trinucleotide=="AGC"))
    return ("Serine");
  else if((trinucleotide=="UAU")||(trinucleotide=="UAC"))
    return ("Tyrosine");
  else if((trinucleotide=="UGG"))
    return ("Tryptophan");
  else if((trinucleotide=="CAA")||(trinucleotide=="CAG"))
    return ("Glutamine");
  else if((trinucleotide=="AAU")||(trinucleotide=="AAC"))
    return ("Asparagine");
  else if((trinucleotide=="CAU")||(trinucleotide=="CAC"))
    return ("Histidine");
  else if((trinucleotide=="GAA")||(trinucleotide=="GAG"))
    return ("Glutamic acid");
  else if((trinucleotide=="GAU")||(trinucleotide=="GAC"))
    return ("Aspartic acid");
  else if((trinucleotide=="AAA")||(trinucleotide=="AAG"))
    return ("Lysine");
  else if((trinucleotide=="CGU")||(trinucleotide=="CGC")||(trinucleotide=="CGA")||
          (trinucleotide=="CGG")||(trinucleotide=="AGA")||(trinucleotide=="AGG"))
    return ("Arginine");
  else if((trinucleotide=="UAA")||(trinucleotide=="UAG")||(trinucleotide=="UGA"))
    return ("Stop");
  else
    cout << "returning unknown" << endl;
  return ("Unknown");
    }