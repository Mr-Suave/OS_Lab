#include "syscall.h"

int main() {
    int fd[2];
    char* msg = "Hello!";
    char buf[10];
    Pipe(fd);
    
    PrintString("Writing...\n");
    Write(msg, 6, fd[1]); // Fill the buffer FIRST
    
    PrintString("Reading...\n");
    Read(buf, 6, fd[0]);  // Read it back
    
    PrintString("Received: ");
    PrintString(buf);
    Halt();

    return 0;
}
    
