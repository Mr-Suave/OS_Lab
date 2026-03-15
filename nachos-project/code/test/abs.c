#include "syscall.h"

int main() {
    int result;

    result = Abs(-65);
    PrintString("Printing the absolute value of -65: ");
    PrintNum(result);
    PrintString("\n");
    Halt();
    /* not reached */
}
