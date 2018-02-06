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
    vector<int> tmp;

    for(i = 0; i < g2size; i++) {
        tmp.push_back(i * gap);
    }
    matrix.push_back(tmp);
    tmp.clear();

    for(i = 1; i < g1size; i++) {
        tmp.push_back(i * gap);
        for(j = 1; j < g2size; j++) {
            tmp.push_back(VINIT);
        }
        matrix.push_back(tmp);
        tmp.clear();
    }
}

int *Global::MakeTraceback() {
    int i, j, m, gapl, gapu;
    int maxScore;
    int *traceback = new int[g1size * g2size * 2];

    for(i = 1; i < g1size; i++) {
        for(j = 1; j < g2size; j++) {
            if(gen1[i] == gen2[j])
                m = matrix[i - 1][j - 1] + 2;
            else
                m = matrix[i - 1][j - 1] - 1;
            gapl = matrix[i][j - 1] - 2;
            gapu = matrix[i - 1][j] - 2;

            maxScore = Max(m, gapl, gapu);
            matrix[i][j] = maxScore;

            if(maxScore == m) {
                //printf("i - 1 = %d, j - 1 = %d\n", i - 1, j - 1);
                traceback[i + g2size * (j + g1size * 0)] = i - 1;
                traceback[i + g2size * (j + g1size * 1)] = j - 1;
            } else if(maxScore == gapl) {
                //printf("i = %d, j - 1 = %d\n", i, j - 1);
                traceback[i + g2size * (j + g1size * 0)] = i;
                traceback[i + g2size * (j + g1size * 1)] = j - 1;
            } else {
                //printf("i - 1 = %d, j = %d\n", i - 1, j);
                traceback[i + g2size * (j + g1size * 0)] = i - 1;
                traceback[i + g2size * (j + g1size * 1)] = j;
            }
        }
    }

    score = maxScore;
    cout << "SCORE = " << score << endl;

    return traceback;
}

void Global::DoAlignment() {
    int i = g1size - 1;
    int j = g2size - 1;
    //vector<char>::iterator iit = gen1align.end() - 1;
    //vector<char>::iterator jit = gen2align.end() - 1;
    vector<char>::iterator iit = gen1align.begin();
    vector<char>::iterator jit = gen2align.begin();
    int *traceback = MakeTraceback();

    printf("g1 = %c, g2 = %c\n", gen1[i], gen2[j]);
    gen1align.push_back(gen1[i]);
    gen2align.push_back(gen2[j]);

    gen1align.insert(iit, 'Q');
    printf("inserted\n");

    while(i >= 1 && j >= 1) {
        //printf("i = %d, j = %d\n", i, j);
        // Match or mismatch
        //printf("0 = %d, 1 = %d\n", traceback[i + g2size * (j + g1size * 0)], traceback[i + g2size * (j + g1size * 1)]);
        if(traceback[i + g2size * (j + g1size * 0)] == i - 1 &&
        traceback[i + g2size * (j + g1size * 1)] == j - 1) {
            printf("g1 = %c, g2 = %c\n", gen1[i - 1], gen2[j - 1]);
            /* printf("Match/mismatch\n");
            printf("\ttraceback[%d][%d][i] = %d\n", i, j, i - 1);
            printf("\ttraceback[%d][%d][j] = %d\n", i, j, j - 1); */
            printf("1 pushing back\n");
            gen1align.push_back(gen1[i - 1]);
            printf("1 pushing back\n");
            gen2align.push_back(gen2[j - 1]);
            i--;
            j--;
            iit++;
            jit++;
            printf("1 done\n");
        }
        else if(traceback[i + g2size * (j + g1size * 0)] == i &&
        traceback[i + g2size * (j + g1size * 1)] == j - 1) {
            printf("g1 = -, g2 = %c\n", gen2[j - 1]);
            //gen1align.push_back('-');
            /* printf("Going left\n");
            printf("\ttraceback[%d][%d][i] = %d\n", i, j, i);
            printf("\ttraceback[%d][%d][j] = %d\n", i, j, j - 1); */
            printf("2 inserting\n");
            gen1align.insert(iit, '-');
            printf("2 pushing back\n");
            gen2align.push_back(gen2[j - 1]);
            j--;
            jit++;
            printf("2 done\n");
        }
        else if(traceback[i + g2size * (j + g1size * 0)] == i - 1 &&
        traceback[i + g2size * (j + g1size * 1)] == j) {
            printf("g1 = %c, g2 = -\n", gen1[i - 1]);
            /* printf("Going up\n");
            printf("\ttraceback[%d][%d][i] = %d\n", i, j, i - 1);
            printf("\ttraceback[%d][%d][j] = %d\n", i, j, j); */
            printf("3 pushing back\n");
            gen1align.push_back(gen1[i - 1]);
            // printf("3 gen2align end = %d", gen2align.end)
            //printf("3 j = %d, inserting at index %d\n", j, gen2align.end() - j);
            printf("3 inserting\n");
            gen2align.insert(jit, '-');
            //gen2align.push_back('-');
            i--;
            iit++;
            printf("3 done\n");
        }
    }

    //Reverse vectors 
    reverse(gen1align.begin(), gen1align.end());
    reverse(gen2align.begin(), gen2align.end());
    gen1align.erase(gen1align.begin());
    gen2align.erase(gen2align.begin());

    //DELETE TRACEBACK
    delete traceback;
}