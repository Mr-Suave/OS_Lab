#include "syscall.h"

int main() {
    int fd[2];
    char buffer[20];
    int pid;
    int bytes;

    if(Pipe(fd) < 0) {
        PrintString("Pipe creation failed!\n");
        Halt();
    }

    pid = Exec("pipe");

    if(pid > 0){
        // parent
        PrintString("Parent: sending msg to child...\n");
        Write("Hello Child!", 13, fd[1]);

        Join(pid);
        PrintString("Parent: child finished. LESGOOO!\n");
        Halt();
    } else {
        // child
        PrintString("Child: Waiting to read from pipe...\n");
        bytes = Read(buffer, 13, fd[0]);

        if (bytes > 0) {
            PrintString("Child Received: ");
            PrintString(buffer);
            PrintString("\n");
        }
        Halt();
    }
}