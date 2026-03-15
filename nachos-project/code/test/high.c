#include "syscall.h"

int main() {
    int i;
    SetPriority(90);
    for (i = 0; i < 5; i++) {
        PrintString("High Priority (90) loop: ");
        PrintNum(i);
        PrintString("\n");
    }

    Exit(0);
}