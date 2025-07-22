// Huseyin Eren YILDIZ, 31047
// Homework 4

/******************************************************************************
Purpose: This program implements a DNA sequences class with lots of operator overloading in it.
Author: HUSEYIN EREN YILDIZ - 31047
Date: 21/04/2024
******************************************************************************/

#include "DNAseq.h"
#include <iostream>
#include <vector>
using namespace std;


DNAseq::DNAseq() {  // Default constructor
// Creates an empty DNA sequence
    length = 0;
    sequence = nullptr;
}


DNAseq::DNAseq(const string & nucleotide) {  // Parametric constructor
// Takes a string as its only parameter and creates a DNA sequence

    length = nucleotide.length();  // variable of lenght of the sequence

    if (length == 0) {
        sequence = new Nucleotide[length];
    }

    else{

        sequence = new Nucleotide[length];  // Memory allocation for the new sequence

        int i=0;
        while(i<length) {
            sequence[i] = Nucleotide(nucleotide[i]);
            i++;
        }
    }
}


DNAseq::DNAseq(const DNAseq & rhs) {  // Deep copy constructor
// It takes a DNAseq object as const-reference parameter and
// creates a new DNAseq object as a deep copy of the parameter

    string temp = rhs.sqnc_getter();  // string version of rhs DNA sequence
    length = rhs.length;
    sequence = new Nucleotide[length];

    int i = 0;

    while(i < rhs.length) {
        sequence[i] = Nucleotide(temp[i]);
        i++;
    }
}

DNAseq::~DNAseq() {  // destructor
// It deletes all dynamically allocated memory and returns them back to the heap
    delete [] sequence;
}


string DNAseq::sqnc_getter() const {
// This function converts sequence to string

    string sqnc= "";
    for (int i=0; i < this->length; i++) {
        sqnc += this -> sequence[i];
    }
    return sqnc;
}


bool DNAseq::operator <= (const DNAseq &rhs) const {
// This operator is used to check whether or not its left hand-side (lhs) operand is a
// subsequence of its right hand-side (rhs) operand.

    int ln = this -> length; // the left hand side DNA sequence's lenght
    int r_ln = rhs.length;  // the right hand side DNA sequence's lenght

    if( ln > r_ln) { // if the lhs object is not a subsequence of the rhs one
        return false;
    }

    int k = 0; // location of rhs (to traverse rhs DNA sequence
    int j = 0; // to traverse lhs DNA sequence

    while (j < ln && k < r_ln) { // Iterate over both sequence to find if 'this' is a subsequence of 'rhs'

        if (this -> sequence[j] == rhs.sequence[k]) {  //  If it finds a matching nucleotide in rhs that
                                                       // matches the current nucleotide in lhs
            j++; // move to next nuc in the lhs DNA sequence
        }
        k++;
    }

    return (j==ln); // If all nucleotide of lhs were found in rhs sequentially after the loop, j should equal to ln
                    // So, it will return true
}


DNAseq DNAseq::operator * (int times) const {
// The operator returns a DNAseq object in which lhs is repeated by rhs times.
// The operator must not change the lhs object itself.

    if (times <= 0) {  // Return an empty DNA sequence if multiplication factor is not positive (degistir)
        return DNAseq();
    }

    string lhsSqnc = this->sqnc_getter();
    string newStr;

    for(int j=0; j < times; j++) {
        newStr += lhsSqnc;
    }

    return DNAseq(newStr);
}


int DNAseq::operator % (const Nucleotide& rhs) const {
// This operator will return the number of occurrences of rhs Nucleotide in the lhs DNAseq object.

    string lhsSqnc = this->sqnc_getter();  // DNA sequence as a standard string for easier processing
    int num_occurrence = 0; // A counter to hold the number of occurrences of rhs Nucleotide in the lhs DNAseq
    char rhsSqnc; // Char variable for holding rhs nucleotide character

    // To convert rhs enum nucleotide to char
    if (rhs == A) {
        rhsSqnc = 'A';
    }
    else if (rhs == T) {
        rhsSqnc = 'T';
    }
    else if (rhs == G) {
        rhsSqnc = 'G';
    }
    else if (rhs == C) {
        rhsSqnc = 'C';
    }
    else {
        rhsSqnc =' ';
    }

    for(int i=0; i < this->length; i++) {  // Iterate over chars in the lhs DNA sequence
        if(lhsSqnc[i] == rhsSqnc) {  // If there is a matching character between lhs and rhs, increase the counter
            num_occurrence++;
        }
    }

    return num_occurrence;  // return the number of occurrences
}


DNAseq DNAseq::operator! () const {
// Every A will be replaced by T, every T will be replaced by A, every G will be replaced by C,
// and every C will be replaced by G. The operator must not change the operand’s value.

    vector <Nucleotide> temp_Seq; // vector to the store first sequence
    for (int k=0; k < this -> length; k++) {
        temp_Seq.push_back(Nucleotide( this -> sequence[k]));  // copy each Nucleotide from the original sequence to temp_Seq

    }

    vector<Nucleotide> temp_Seq2;  // vector to hold the complement of a DNA sequence

    for (int i=0; i< temp_Seq.size(); i++) {  //  Loop through each Nucleotide in the original sequence vector

        // Verify the Nucleotide and add its complement to temp_Seq2
        if (temp_Seq[i] == Nucleotide('A')) {
            temp_Seq2.push_back(T);
        }
        else if (temp_Seq[i] == Nucleotide('T')) {
            temp_Seq2.push_back(A);
        }
        else if (temp_Seq[i] == Nucleotide('G')) {
            temp_Seq2.push_back(C);
        }
        else if (temp_Seq[i] == Nucleotide('C')) {
            temp_Seq2.push_back(G);
        }
    }

    string Sqnc; // String variable to hold complemented sequence
    for (int k =0; k < temp_Seq2.size(); k++) {

        // Change each Nucleotide in the complemented sequence into its character form
        if (temp_Seq2[k] == A) {
            Sqnc += 'A';
        }
        else if (temp_Seq2[k] == T) {
            Sqnc += 'T';
        }
        else if (temp_Seq2[k] == G) {
            Sqnc += 'G';
        }
        else if (temp_Seq2[k] == C) {
            Sqnc += 'C';
        }
    }

    return DNAseq(Sqnc);  // Finally, it will return a new DNAseq using Sqnc string
}


DNAseq &DNAseq::operator = (const DNAseq & rhs) {

    string rhs_sqnc = rhs.sqnc_getter();  // convert DNAseq rhs to string
    string lhs_sqnc = this->sqnc_getter();  // convert DNAseq lhs to string

    if (rhs_sqnc == lhs_sqnc) {  // Check if the sequences are identical
        if (this == &rhs) {
            return *this;  // return the current instance unchanged
        }

        length = rhs.length;
        return *this;
    }

    delete [] sequence;  // to avoiding memory leaks
    sequence = new Nucleotide[rhs.length]; // allocate memory for the sequence to match the size of rhs, creating new space as needed
    length = rhs.length; // update the length again

    int i=0;

    while(i < rhs.length){  // copying process from rhs to Nucleotide object

        sequence[i] = Nucleotide(rhs_sqnc[i]);
        i++;
    }

    return *this;  // return
}


DNAseq operator + (const DNAseq &lhs, const DNAseq &rhs) {
// It will behave in one of two ways based on whether the first nucleotide of the rhs object exists in the lhs or not.

    string lhsSqnc = lhs.sqnc_getter();  // convert DNAseq lhs to string
    string rhsSqnc = rhs.sqnc_getter();  // convert DNAseq rhs to string

/* Start: I took these code parts from CS201 - W4 page 21 and I updated it */
    if (lhsSqnc.find(rhsSqnc[0]) != string::npos) {
        // If it existsthe operator will return a DNAseq object, of which the content is the lhs
        // object’s sequence with rhs object sequence inserted just after the first occurrence of
        // this first nucleotide.

        lhsSqnc.insert(lhsSqnc.find(rhsSqnc[0])+1,rhsSqnc);
    }
    else {  // If it doesn't exist, concatenate rhs at the end of lhs
        lhsSqnc += rhsSqnc;
    }
/* End: I took these code parts from CS201 - W4 page 21 and I updated it */

    return DNAseq(lhsSqnc);  // return new DNAseq using modified lhsSqnc
}


DNAseq operator + (const Nucleotide & lhs, const DNAseq & rhs) {
// It returns a DNAseq object, in which lhs is prepended (added to the beginning) to rhs.

    char temp; // to hold lhs Nucleotide

    // enum lhs Nucleotide to corresponding char
    if (lhs == A) {
        temp = 'A';
    }
    else if (lhs == T) {
        temp = 'T';
    }
    else if (lhs == G) {
        temp = 'G';
    }
    else if (lhs == C) {
        temp = 'C';
    }
    else {  // for unforeseen situations
        temp=' ';
    }

    string rhsSqnc = rhs.sqnc_getter();  // convert DNAseq rhs to string
    string newStr = temp + rhsSqnc; // Form a new string with temp(char lhs) and rhsSqnc

    DNAseq final_Sqnc (newStr);  // create a DNAseq object using newStr

    return final_Sqnc;  // return new DNAseq object
}


DNAseq operator - (const DNAseq &lhs , const DNAseq &rhs) { // Remove sequence
// post: Removes first occurrence of RHS from LHS and returns the resulting string. Returns lhs if rhs does not occur any.

    string lhsSqnc = lhs.sqnc_getter();  // convert DNAseq lhs to string
    string rhsSqnc = rhs.sqnc_getter();  // convert DNAseq rhs to string

/* Start: I took these code part from CS201 - W4 page 21 and I updated it */

    string temp = lhsSqnc;  // a string variable to provide modified lhs sequence
    int location = lhsSqnc.find(rhsSqnc); // first occurence of rhs sequence in the lhs sequence

    if (location != string::npos) {  // If rhs sequence is found in lhs sequence

        temp = lhsSqnc.substr(0,location) + lhsSqnc.substr(location+rhsSqnc.length(),lhsSqnc.length());
    }

// End: I took these code part from CS201 - W4 page 21 and I updated it

    return DNAseq(temp);  // return new DNAseq object
}


DNAseq &DNAseq::operator += (const DNAseq & rhs) {
// It modifies its current lhs DNAseq object by adding (+) the rhs DNAseq object to it.

    // Start: Used code from Week-6 Lab / ComplexNumber.cpp and updated according to this program
    *this = *this + rhs;  // Call + operator to merge *this and rhs
    return *this;   // after adding, return *this value
}


ostream& operator << (ostream& output, const DNAseq& rhs) {
// Using for displaying the content of a DNA sequence.

    // Start: Used code from Week-6 Lab / ComplexNumber.cpp and updated according to this program
    output << rhs.sqnc_getter();
    return output;  // Return the output stream to allow chaining of output operations
}