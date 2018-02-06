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

    for(i = 0; i <= g2size; i++) {
        tmp.push_back(i * gap);
    }
    matrix.push_back(tmp);

    tmp.clear();

    for(i = 1; i <= g1size; i++) {
        tmp.push_back(i * gap);
        for(j = 1; j <= g2size; j++) {
            tmp.push_back(VINIT);
        }
        matrix.push_back(tmp);
        tmp.clear();
    }
}

void Global::ComputeScore() {
    int i = 0, j = 0, m = 0, gapl = 0, gapu = 0;
    int maxScore = 0;
    int traceback[g1size][g2size][2];

    for(i = 1; i <= g1size; i++) {
        for(j = 1; j <= g2size; j++) {
            //cout << "1" << endl;
            if(gen1[i] == gen2[j]) {
                m = matrix[i - 1][j - 1] + 2;
            } else {
                m = matrix[i - 1][j - 1] - 1;
            }
            gapl = matrix[i][j - 1] - 2;
            gapu = matrix[i - 1][j] - 2;

            //cout << "2" << endl;

            maxScore = Max(m, gapl, gapu);
            matrix[i][j] = maxScore;
            printf("matrix[%d][%d] = %d\n", i, j, maxScore);

            //cout << "3" << endl;

            if(maxScore == m) {
                //cout << "4" << endl;
                traceback[i][j][0] = i - 1;
                traceback[i][j][1] = j - 1;
                //cout << "4" << endl;
            } else if(maxScore == gapl) {
                //cout << "5" << endl;
                traceback[i][j][0] = i;
                traceback[i][j][1] = j - 1;
                //cout << "5" << endl;
            } else {
                //cout << "6" << endl;
                traceback[i][j][0] = i - 1;
                traceback[i][j][1] = j;
                //cout << "6" << endl;
            }
        }
    }

    score = maxScore;
    cout << "SCORE = " << score << endl;
}