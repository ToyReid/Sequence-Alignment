#include "align.hpp"
using namespace std;

enum Alignment {unknown = 0, global, local, endgapfree};

int main(int argc, char **argv) {
    string file1, file2, align;
    ifstream fasta1, fasta2;
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
        fasta1.open(file1);
        if(!fasta1) fprintf(stderr, "\t%s NOT OPENED. Please try again.\n", file1.c_str());
        else {
            printf("\t%s OPENED\n", file1.c_str());
            break;
        }
    }

    while(1) {
        cout << "Second .fasta filename: ";
        cin >> file2;
        fasta2.open(file2);
        if(!fasta2) fprintf(stderr, "\t%s NOT OPENED. Please try again.\n", file2.c_str());
        else {
            printf("\t%s OPENED\n", file2.c_str());
            break;
        }
    }

    cout << "Please enter scoring parameters (space delimited) for\nMatch Mismatch Gap: ";
    cin >> match >> mismatch >> gap;
    
    printf("\nComputing the %s alignment of %s and %s.\n\tMatch = %d, Mismatch = %d, Gap = %d\n\n",
        align.c_str(), file1.c_str(), file2.c_str(), match, mismatch, gap);

    if(a == global) {
        Global g;
        g.Init(fasta1, fasta2, match, mismatch, gap);
        g.SetupMatrix();
        //g.PrintMatrix();
        // CALL TRACEBACK
        g.MakeTraceback();
        g.DoAlignment();
        g.PrintAlignment();
        //g.PrintMatrix();
    } else if(a == local) {
        Local l;
        l.Init(fasta1, fasta2, match, mismatch, gap);
        l.SetupMatrix();
        l.MakeTraceback();
        l.DoAlignment();
        l.PrintAlignment();
    } else if(a == endgapfree) {
        EndGapFree e;
        e.Init(fasta1, fasta2, match, mismatch, gap);
        e.SetupMatrix();
        e.DoAlignment();
    }
    
    return 0;
}