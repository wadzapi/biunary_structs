#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

#include "struct_factory.hh"

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
    StructFactory<int> struct_factory(10, 16);
    /*/// Stack test
    Stack<int>* stack = struct_factory.MakeStack();
    printf("Pushing: ");
    for (int i = 1; i < 11; i++) {
        stack->Push(i);
        printf("%i; ", i);
    }
    printf("\n");
    printf("Popping: ");
    for (int i = 1; i < 11; i++) {
        int k = *(stack->Top());
        stack->Pop();
        printf("%i; ", k);
    }
    printf("\n");
*/

    //// Queue test
    Queue<int> *queue = struct_factory.MakeQueue();
    printf("Pushing: ");
    for (int i = 1; i < 11; i++) {
        queue->Push(i);
        printf("%i; ", i);
    }
    printf("\n");
    printf("Popping: ");
    for (int i = 1; i < 11; i++) {
        int k = *(queue->Front());
        queue->Pop();
        printf("%i; ", k);
    }
    printf("\n");

/*  //// Sequence test
    Sequence<int> *seq = struct_factory.MakeSequence();
    //like stack
    printf("Pushing: ");
    for (int i = 1; i < 11; i++) {
        seq->PushBack(i);
        printf("%i; ", i);
    }
    printf("\n");
    printf("Popping: ");
    for (int i = 1; i < 11; i++) {
        int k = *(seq->Back());
        seq->PopBack();
        printf("%i; ", k);
    }
    printf("\n");
*/
    
    return 0;
}
