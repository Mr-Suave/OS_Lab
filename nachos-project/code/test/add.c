/* add.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"

int main() {
    //int result;

    //result = Add(42, 23);
    int i;
    for(i=0;i<1000000;i++){
        PrintString("hello!\n");
    }
    /* not reached */
}
