/* exec.c
 *	Simple program to test the exec system call.
 */

#include "syscall.h"
#define stdin 0
#define stdout 1

int main() {
    int pid;
    pid = Exec("num_io");
    if (pid < 0) {
        Write("Exec failed: ", 14, stdout);
        PrintNum(pid);
    } else if (pid>0) {
        int i;
        for(i = 0; i<10000; i++){
            int j;
            for(j = 0; j<200000; j++);
            PrintString("I Am Parent!\n");
        }
    } else if (pid == 0){
        int k;
        for(k = 0; k<10000; k++){
            int m;
            for(m= 0; m<200000; m++);
            PrintString("I Am Child!\n");
        }
    } else {
        Join();
    }
}
