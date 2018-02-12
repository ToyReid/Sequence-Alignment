#include "align.hpp"
using namespace std;

void Local::SetupMatrix() {
    int i, j;
    Cell *c;
    vector<Cell *> tmp;

    for(i = 0; i < g2size; i++) {
        c = new Cell;
        c->val = 0;
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
        c->val = 0;
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

void Local::MakeTraceback() {
    int i, j, m, gapl, gapu;
    int maxScore;

    for(i = 1; i < g1size; i++) {
        for(j = 1; j < g2size; j++) {
            if(matrix[i][j]->g1 == matrix[i][j]->g2)
                m = matrix[i - 1][j - 1]->val + match;
            else {
                m = matrix[i - 1][j - 1]->val + mismatch;
                if(m < 0) m = 0;
            }
            gapl = matrix[i][j - 1]->val + gap;
            if(gapl < 0) gapl = 0;
            gapu = matrix[i - 1][j]->val + gap;
            if(gapu < 0) gapu = 0;

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
    //cout << "GLOBAL SCORE = " << score << endl;

    max = matrix[g1size - 1][g2size - 1];
}

void Local::FindBest() {
    int i, j;
    score = 0;

    for(i = 1; i < g1size; i++) {
        for(j = 1; j < g2size; j++) {
            if(matrix[i][j]->val > score) {
                score = matrix[i][j]->val;
                max = matrix[i][j];
            }
        }
    }
}

void Local::DoAlignment() {
    int i, j;
    vector<char> tmp;
    Cell *c;

    FindBest();
    c = max;
    i = c->i - 1;
    j = c->j - 1;

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

    while((c->trace != nullptr) && (c->trace->val != 0)) {
        //printf("i = %d, j = %d\n", i, j);
        //printf("c->trace->val = %d\n", c->trace->val);
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
            //printf("g1 = -, g2 = %c\n", c->g2);
            printMat[0].push_back('-');
            printMat[1].push_back(' ');
            printMat[2].push_back(c->g2);
        } else if(c->trace == matrix[i - 1][j]) {   // gap up
            i--;
            //printf("g1 = %c, g2 = -\n", c->g1);
            printMat[0].push_back(c->g1);
            printMat[1].push_back(' ');
            printMat[2].push_back('-');
        }
        c = c->trace;
    }
}