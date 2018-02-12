#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

#define VINIT 0
#define LINE_LENGTH 70
#define MIN -10000

struct Cell {
    int val;
    int i;
    int j;
    char g1;
    char g2;
    Cell *trace;
    Cell();
};

class Align {
protected:
    Cell *max;
    int score;
    int match;
    int mismatch;
    int gap;
    int g1size;
    int g2size;
    vector<vector<Cell *> > matrix;
    vector<vector<char> > printMat;
    vector<char> gen1;
    vector<char> gen2;
public:
    Align();
    ~Align();
    int Max(int a, int b, int c);
    void Init(ifstream&, ifstream&, int, int, int);
    void ReadSequences(ifstream &fasta1, ifstream &fasta2);
    void PrintMatrix();
    void PrintAlignment();
    virtual void SetupMatrix() = 0;
    virtual void MakeTraceback() = 0;
    virtual void DoAlignment() = 0;
    virtual void FindBest() = 0;
};

class Global : public Align {
public:
    void SetupMatrix();
    void MakeTraceback();
    void DoAlignment();
    void FindBest(){};
};

class Local : public Align {
public:
    void SetupMatrix();
    void MakeTraceback();
    void DoAlignment();
    void FindBest();
};

class EndGapFree : public Align {
public:
    void SetupMatrix();
    void MakeTraceback();
    void FindBest();
    void DoAlignment();
};