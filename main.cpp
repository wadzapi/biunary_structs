#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include "sequence.hh"


int main(int argc, char** argv) {
    /*FILE *inputFile = stdin;
    FILE *outputFile = stdout;
    char oFilename[128] = { "" };
    char iFilename[128] = { "" };
    int opt;
    while ((opt = getopt(argc, argv, "i:o:")) != EOF) {
        switch(opt) {
            case 'i':
                strcpy(iFilename, optarg);
                break;
            case 'o':
                strcpy(oFilename, optarg);
                break;
        }
    }
    if (strlen(iFilename) > 0) {
        if ((inputFile = fopen(iFilename, "rt")) == NULL) {
            fprintf(stderr, "Cannot open input file %s\n", iFilename);
            exit(1);
        }
    }
    if (strlen(oFilename) > 0) {
        if ((outputFile = fopen(oFilename, "wt")) == NULL) {
            fprintf(stderr, "Cannot open output file %s\n", oFilename);
            exit(1);
        }
    }*/
    Sequence<int> q(10);
    for (int i = 1; i < 11; i++) {
        q.PushFront(i);
    }
    ///like stack
    for (int i = 1; i < 11; i++) {
        int k = *(q.Front());
        q.PopFront();
    }
    return 0;
}
