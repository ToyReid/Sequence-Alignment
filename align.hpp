#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <limits>
using namespace std;

#define VINIT 0

class Align {
protected:
    int score;
    int match;
    int mismatch;
    int gap;
    int g1size;
    int g2size;
    vector<vector<int> > matrix;
    vector<char> gen1;
    vector<char> gen2;
public:
    int Max(int a, int b, int c);
    void Init(ifstream&, ifstream&, int, int, int);
    void ReadSequences(ifstream &fasta1, ifstream &fasta2);
    void PrintMatrix();
    virtual void SetupMatrix()= 0;
    virtual void ComputeScore()= 0;};

class Global : public Align {
public:
    void SetupMatrix();
    void ComputeScore();
};

class Local : public Align {
public:
    virtual void SetupMatrix()= 0;
    void ComputeScore();
};

class EndGapFree : public Align {
    virtual void SetupMatrix()= 0;
    void ComputeScore();
};