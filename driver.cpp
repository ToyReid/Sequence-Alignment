#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

enum Alignment {unknown = 0, global, local, endgapfree};

/* 
    T[i,j] = Score of optimally aligning
                first i bases of s with
                first j bases of t

                 {T[i-1, j-1] + score(s[i], t[j])
    T[i,j] = max {T[i-1, j] + g
                 {T[i, j-1] + g
*/

int main(int argc, char **argv) {
    string file1, file2, align;
    ifstream gen1, gen2;
    int match, mismatch, gap;
    Alignment a;

    while(1) {
        cout << "Alignment to compute (global, local, or endgapfree): ";
        cin >> align;

        if(align == "global") {
            a = global;
            break;
        } else if(align == "local") {
            a = local;
            break;
        } else if(align == "endgapfree") {
            a = endgapfree;
            break;
        } else {
            a = unknown;
            cerr << "\tInvalid alignment type. Please try again." << endl;
        }
    }

    while(1) {
        cout << "First .fasta filename: ";
        cin >> file1;
        gen1.open(file1);
        if(!gen1) fprintf(stderr, "\t%s NOT OPENED. Please try again.\n", file1.c_str());
        else {
            printf("\t%s OPENED\n", file1.c_str());
            break;
        }
    }

    while(1) {
        cout << "Second .fasta filename: ";
        cin >> file2;
        gen2.open(file2);
        if(!gen2) fprintf(stderr, "\t%s NOT OPENED. Please try again.\n", file2.c_str());
        else {
            printf("\t%s OPENED\n", file2.c_str());
            break;
        }
    }

    cout << "Please enter scoring parameters (space delimited) for\nMatch Mismatch Gap: ";
    cin >> match >> mismatch >> gap;
    
    printf("\nComputing the %s alignment of %s and %s.\n\tMatch = %d, Mismatch = %d, Gap = %d\n",
        align.c_str(), file1.c_str(), file2.c_str(), match, mismatch, gap);
    
    return 0;
}