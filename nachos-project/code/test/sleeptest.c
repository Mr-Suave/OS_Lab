#include "syscall.h"

int main() {
    int i;

    PrintString("Starting sleep test...\n");

    for (i = 0; i < 5; i++) {
        PrintString("Going to sleep for 10000 ticks...\n");
        
        Sleep(10000);
        
        PrintString("I am awake now!\n");
    }

    PrintString("Sleep test finished.\n");
    Halt();
}
