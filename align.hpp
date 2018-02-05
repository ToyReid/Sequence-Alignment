#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
using namespace std;

class Align {
protected:
    int score;
    int match;
    int mismatch;
    int gap;
    vector<vector<int> > matrix;
    vector<char> gen1;
    vector<char> gen2;
public:
    Align();
    Align(ifstream&, ifstream&, int, int, int);
    void ReadSequences(ifstream &fasta1, ifstream &fasta2);
    void PrintMatrix(vector<vector<int> >);
    virtual void ComputeScore()= 0;
};

class Global : public Align {
public:
    void ComputeScore();
};

class Local : public Align {
public:
    void ComputeScore();
};

class EndGapFree : public Align {
    void ComputeScore();
};