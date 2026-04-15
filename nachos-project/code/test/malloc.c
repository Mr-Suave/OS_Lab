#include "syscall.h"

int main() {
    int *dynamicArray;
    int size = 5;
    
    // Calling Malloc directly because it's in start.s
    dynamicArray = (int *)Malloc(size * 4); 

    if (dynamicArray != 0) {
        PrintString("Malloc successful!\n");
        dynamicArray[0] = 100;
        Free((int)dynamicArray);
    }

    Halt();
}