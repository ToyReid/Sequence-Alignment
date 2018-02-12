#include "align.hpp"
using namespace std;

/* 
    T[i,j] = Score of optimally aligning
                first i bases of s with
                first j bases of t

                 {T[i-1, j-1] + score(s[i], t[j])
    T[i,j] = max {T[i-1, j] + g
                 {T[i, j-1] + g
*/

void Global::SetupMatrix() {
    int i, j;
    Cell *c;
    vector<Cell *> tmp;

    printf("g1size = %d\n", g1size);
    printf("g2size = %d\n", g2size);

    for(i = 0; i < g2size; i++) {
        c = new Cell;
        c->val = i * gap;
        c->j = i;
        c->i = 0;
        c->g1 = gen1[0];
        c->g2 = gen2[i];
        tmp.push_back(c);
    }
    matrix.push_back(tmp);
    tmp.clear();

    for(i = 1; i < g1size; i++) {
        c = new Cell;
        c->val = i * gap;
        c->i = i;
        c->j = 0;
        c->g1 = gen1[i];
        c->g2 = gen2[0];
        tmp.push_back(c);
        for(j = 1; j < g2size; j++) {
            c = new Cell;
            c->val = VINIT;
            c->i = i;
            c->j = j;
            c->g1 = gen1[i];
            c->g2 = gen2[j];
            tmp.push_back(c);
        }
        matrix.push_back(tmp);
        tmp.clear();
    }
}

void Global::MakeTraceback() {
    int i, j, m, gapl, gapu;
    int maxScore;

    for(i = 1; i < g1size; i++) {
        for(j = 1; j < g2size; j++) {
            if((i > 1 && j > 1) || (i == 1 && j == 1)) {
                //printf("i = %d, j = %d\n", i, j);
                if(matrix[i][j]->g1 == matrix[i][j]->g2)
                    m = matrix[i - 1][j - 1]->val + match;
                else
                    m = matrix[i - 1][j - 1]->val + mismatch;
            } else m = MIN;
            gapl = matrix[i][j - 1]->val + gap;
            gapu = matrix[i - 1][j]->val + gap;

            maxScore = Max(m, gapl, gapu);
            matrix[i][j]->val = maxScore;

            if(maxScore == m) {
                matrix[i][j]->trace = matrix[i - 1][j - 1];
            } else if(maxScore == gapl) {
                matrix[i][j]->trace = matrix[i][j - 1];
            } else {
                matrix[i][j]->trace = matrix[i - 1][j];
            }
        }
    }
    score = maxScore;
    max = matrix[g1size - 1][g2size - 1];
}

void Global::DoAlignment() {
    int i = g1size - 2;
    int j = g2size - 2;
    vector<char> tmp;
    Cell *c = max;

    //if(matrix[1][1]->trace == matrix[0][0]) printf("OK GOOD\n");

    // Initialize print matrix
    tmp.push_back(c->g1);
    printMat.push_back(tmp);
    tmp.clear();

    if(c->g1 == c->g2) tmp.push_back('|');
    else tmp.push_back(' ');
    printMat.push_back(tmp);
    tmp.clear();

    tmp.push_back(c->g2);
    printMat.push_back(tmp);
    tmp.clear();
    c = c->trace;

    while(c->trace != nullptr) {
        //printf("i = %d, j = %d\n", i, j);
        if(c->trace == matrix[i - 1][j - 1]) {  // diagonal movement
            i--; j--;
            //printf("g1 = %c, g2 = %c\n", c->g1, c->g2);
            //printf("pm[0].push(%c)\tpm[2].push(%c)\n", c->g1, c->g2);
            printMat[0].push_back(c->g1);
            printMat[2].push_back(c->g2);
            if(c->g1 == c->g2)  // match  
                printMat[1].push_back('|');
            else
                printMat[1].push_back(' ');
        } else if(c->trace == matrix[i][j - 1]) {   // gap left
            j--;
            printMat[0].push_back('-');
            printMat[1].push_back(' ');
            printMat[2].push_back(c->g2);
        } else if(c->trace == matrix[i - 1][j]) {   // gap up
            i--;
            printMat[0].push_back(c->g1);
            printMat[1].push_back(' ');
            printMat[2].push_back('-');
        }
        c = c->trace;
    }
    //DELETE TRACEBACK
}