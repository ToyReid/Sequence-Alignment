#include "align.hpp"
using namespace std;

Align::Align() {
    score = 0;
    match = 0;
    mismatch = 0;
    gap = 0;
}

Align::Align(ifstream &fasta1, ifstream &fasta2,
int match, int mismatch, int gap) {
    score = 0;
    this->match = match;
    this->mismatch = mismatch;
    this->gap = gap;
    ReadSequences(fasta1, fasta2);
}

void Align::ReadSequences(ifstream &fasta1, ifstream &fasta2) {
    string line;
    int i;
    
    getline(fasta1, line); //skip first line
    while(fasta1) {
        getline(fasta1, line);
        for(i = 0; i < line.size(); i++) {
            gen1.push_back(line[i]);
        }
    }

    getline(fasta2, line);
    while(fasta2) {
        getline(fasta2, line);
        for(i = 0; i < line.size(); i++) {
            gen2.push_back(line[i]);
        }
    }
}

void Align::PrintMatrix(vector<vector<int> >) {
    
}