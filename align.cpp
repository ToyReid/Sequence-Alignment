#include "align.hpp"
using namespace std;

Align::Align(){}
Align::~Align(){}

int Align::Max(int m, int gapl, int gapu) {
    int max;

    if(gapl >= gapu)
        max = gapl;
    else
        max = gapu;
    if(m >= max)
        max = m;

    return max;
}

void Align::Init(ifstream &fasta1, ifstream &fasta2,
int iMatch, int iMismatch, int iGap) {
    score = 0;
    match = iMatch;
    mismatch = iMismatch;
    gap = iGap;
    ReadSequences(fasta1, fasta2);
}

void Align::ReadSequences(ifstream &fasta1, ifstream &fasta2) {
    string line;
    int i;
    
    getline(fasta1, line); //skip first line
    gen1.push_back('0'); //align genome with matrix
    while(fasta1) {
        getline(fasta1, line);
        for(i = 0; i < line.size(); i++) {
            gen1.push_back(line[i]);
        }
    }

    getline(fasta2, line);
    gen2.push_back('0');
    while(fasta2) {
        getline(fasta2, line);
        for(i = 0; i < line.size(); i++) {
            gen2.push_back(line[i]);
        }
    }

    g1size = gen1.size();
    g2size = gen2.size();
}

void Align::PrintMatrix() {
    int i, j;

    printf("\n");
    for(i = 0; i < matrix.size(); i++) {
        for(j = 0; j < matrix[0].size(); j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void Align::PrintAlignment() {
    int i, j;
    int size = gen1align.size();

    printf("size = %d\n", gen1align.size() % LINE_LENGTH);

    for(i = 0; i < (size / LINE_LENGTH) + 1; i++) {
        for(j = i * LINE_LENGTH; j < i * LINE_LENGTH + LINE_LENGTH; j++) {
            if(j >= size) break;
            printf("%c", gen1align[j]);
        }
        printf("\n");
        for(j = i * LINE_LENGTH; j < i * LINE_LENGTH + LINE_LENGTH; j++) {
            if(j >= size) break;
            printf("|");
        }
        printf("\n");
        for(j = i * LINE_LENGTH; j < i * LINE_LENGTH + LINE_LENGTH; j++) {
            if(j >= size) break;
            printf("%c", gen2align[j]);
        }
        printf("\n");
    }
}