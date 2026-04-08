/**************************************************************
 *
 * userprog/ksyscallhelper.h
 *
 * Helper function for ksyscall.h
 *
 * by Thuc Le.
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALLHELPER_H__
#define __USERPROG_KSYSCALLHELPER_H__

#include "kernel.h"
#include "synchconsole.h"

#define LF ((char)10)
#define CR ((char)13)
#define TAB ((char)9)
#define SPACE ((char)' ')

/* maximum length of an interger (included the minus sign) */
#define MAX_NUM_LENGTH 11
/* A buffer to read and write number */
char _numberBuffer[MAX_NUM_LENGTH + 2];

char isBlank(char c) { return c == LF || c == CR || c == TAB || c == SPACE; }

/**
 * Read and store characters in the _numberBuffer until blank
 * or end of file
 *
 * It will read at most MAX_NUM_LENGTH + 1 character
 **/
void readUntilBlank() {
    memset(_numberBuffer, 0, sizeof(_numberBuffer));
    char c = kernel->synchConsoleIn->GetChar();

    if (c == EOF) {
        DEBUG(dbgSys, "Unexpected end of file - number expected");
        return;
    }

    if (isBlank(c)) {
        DEBUG(dbgSys, "Unexpected white-space - number expected");
        return;
    }

    int n = 0;

    while (!(isBlank(c) || c == EOF)) {
        _numberBuffer[n++] = c;
        if (n > MAX_NUM_LENGTH) {
            DEBUG(dbgSys, "Number is too long");
            return;
        }
        c = kernel->synchConsoleIn->GetChar();
    }
}

// implemented for malloc 
void copyFromUser(int vaddr, char* kernelBuffer, int size) {
    for (int i = 0; i < size; i++) {
        int data;
        // Read 1 byte from user virtual address
        kernel->machine->ReadMem(vaddr + i, 1, &data);
        kernelBuffer[i] = (char)data;
    }
}

void copyToUser(int vaddr, char* kernelBuffer, int size) {
    for (int i = 0; i < size; i++) {
        // Write 1 byte to user virtual address
        kernel->machine->WriteMem(vaddr + i, 1, (int)kernelBuffer[i]);
    }
}

/**
 * Return true of the interger equals to the
 * interger stored in the string
 **/
bool compareNumAndString(int integer, const char *s) {
    if (integer == 0) return strcmp(s, "0") == 0;

    int len = strlen(s);

    if (integer < 0 && s[0] != '-') return false;

    if (integer < 0) s++, --len, integer = -integer;

    while (integer > 0) {
        int digit = integer % 10;

        if (s[len - 1] - '0' != digit) return false;

        --len;
        integer /= 10;
    }

    return len == 0;
}

#endif /* ! __USERPROG_KSYSCALLHELPER_H__ */
