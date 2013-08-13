#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

#include "struct_factory.hh"

int main(int argc, char** argv) {
    StructFactory<int> struct_factory(10, 16);
    //// Stack test
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


    /*/// Queue test
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
*/

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
