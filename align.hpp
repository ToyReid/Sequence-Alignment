#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <limits>
using namespace std;

#define VINIT 0
#define LINE_LENGTH 70

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
    vector<char> gen1align;
    vector<char> gen2align;
public:
    Align();
    ~Align();
    int Max(int a, int b, int c);
    void Init(ifstream&, ifstream&, int, int, int);
    void ReadSequences(ifstream &fasta1, ifstream &fasta2);
    void PrintMatrix();
    void PrintAlignment();
    virtual void SetupMatrix() = 0;
    virtual int *MakeTraceback() = 0;
    virtual void DoAlignment() = 0;
};

class Global : public Align {
public:
    void SetupMatrix();
    int *MakeTraceback();
    void DoAlignment();
};

class Local : public Align {
public:
    void SetupMatrix();
    int *MakeTraceback();
    void DoAlignment();
};

class EndGapFree : public Align {
public:
    void SetupMatrix();
    int *MakeTraceback();
    void DoAlignment();
};