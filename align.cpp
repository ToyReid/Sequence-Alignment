#include "align.hpp"
using namespace std;

Cell::Cell() {
    val = 0;
    trace = nullptr;
    g1 = '\0';
    g2 = '\0';
}

Align::Align(){}
Align::~Align(){
    // IMPLEMENT
}

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
            printf("%5d", matrix[i][j]->val);
        }
        printf("\n");
    }
    printf("\n");
}

void Align::PrintAlignment() {
    int i, j;
    int size = printMat[0].size();

    //printf("size = %d\n", printMat[0].size());

    for(i = 0; i < size / LINE_LENGTH + 1; i++) {
        printf("Genome 1: ");
        for(j = size - 1 - i * LINE_LENGTH;
        (j > (size - 1 - i * LINE_LENGTH) - LINE_LENGTH) && (j >= 0);
        j--) {
            //printf("1: j = %d\n", j);
            printf("%c", printMat[0][j]);
        }
        printf("\n");
        printf("          ");
        for(j = size - 1 - i * LINE_LENGTH;
        (j > (size - 1 - i * LINE_LENGTH) - LINE_LENGTH) && (j >= 0);
        j--) {
            //printf("2: j = %d\n", j);
            printf("%c", printMat[1][j]);
        }
        printf("\n");
        printf("Genome 2: ");
        for(j = size - 1 - i * LINE_LENGTH;
        (j > (size - 1 - i * LINE_LENGTH) - LINE_LENGTH) && (j >= 0);
        j--) {
            //printf("3: j = %d\n", j);
            printf("%c", printMat[2][j]);
        }
        printf("\n\n");
    }

    printf("Alignment Score = %d\n", score);
}