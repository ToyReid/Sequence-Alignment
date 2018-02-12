#include "align.hpp"
using namespace std;

void EndGapFree::SetupMatrix() {
    int i, j;
    Cell *c;
    vector<Cell *> tmp;

    for(i = 0; i < g2size; i++) {
        c = new Cell;
        c->val = 0;
        c->g1 = gen1[0];
        c->g2 = gen2[i];
        tmp.push_back(c);
    }
    matrix.push_back(tmp);
    tmp.clear();

    for(i = 1; i < g1size; i++) {
        c = new Cell;
        c->val = 0;
        c->g1 = gen1[i];
        c->g2 = gen2[0];
        tmp.push_back(c);
        for(j = 1; j < g2size; j++) {
            c = new Cell;
            c->val = VINIT;
            c->g1 = gen1[i];
            c->g2 = gen2[j];
            tmp.push_back(c);
        }
        matrix.push_back(tmp);
        tmp.clear();
    }
}

void EndGapFree::MakeTraceback() {
    int i, j, m, gapl, gapu;
    int maxScore;

    for(i = 1; i < g1size; i++) {
        for(j = 1; j < g2size; j++) {
            if(matrix[i][j]->g1 == matrix[i][j]->g2)
                m = matrix[i - 1][j - 1]->val + match;
            else
                m = matrix[i - 1][j - 1]->val + mismatch;
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

void EndGapFree::FindBest() {
    int i;
    score = 0;

    for(i = 1; i < g1size; i++) {
        if(matrix[i][g2size - 1]->val > score) {
            score = matrix[i][g2size - 1]->val;
            max = matrix[i][g2size - 1];
        }
    }
    for(i = 1; i < g2size; i++) {
        if(matrix[g1size - 1][i]->val > score) {
            score = matrix[g1size - 1][i]->val;
            max = matrix[g1size - 1][i];
        }
    }
}

void EndGapFree::DoAlignment() {
    MakeTraceback();
    FindBest();

    printf("Score = %d\n", score);
}