#include "syscall.h"

int main() {
    int i;
    SetPriority(10); 

    for (i = 0; i < 5; i++) {
        PrintString("Low Priority (10) loop: ");
        PrintNum(i);
        PrintString("\n");
    }

    Exit(0);
}