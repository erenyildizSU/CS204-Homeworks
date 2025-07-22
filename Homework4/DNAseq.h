// Created by Huseyin Eren YILDIZ on 17.04.2024.

#ifndef HOMEWORK4_DNASEQ_H
#define HOMEWORK4_DNASEQ_H

#include <iostream>
#include <string>

using namespace std;
enum Nucleotide { A, C, G, T };

class DNAseq {

private:

    int length;
    Nucleotide * sequence;

public:

    DNAseq();
    DNAseq(const string& str);
    DNAseq(const DNAseq& rhs);
    ~DNAseq();

    string sqnc_getter() const;
    DNAseq& operator = (const DNAseq&);
    DNAseq& operator += (const DNAseq& );
    DNAseq operator * (int n) const;
    DNAseq operator ! () const;
    int operator % (const Nucleotide&) const;
    bool operator <= (const DNAseq&) const;
};

DNAseq operator + (const DNAseq&, const DNAseq&);
DNAseq operator - (const DNAseq&, const DNAseq&);
DNAseq operator + (const Nucleotide&, const DNAseq& );
ostream& operator << (ostream&, const DNAseq&);

#endif //HOMEWORK4_DNASEQ_H
